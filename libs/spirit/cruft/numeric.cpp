#include <cstdio>
#include <vector>

#include <boost/spirit/home/qi/nonterminal.hpp>
#include <boost/spirit/home/qi/operator.hpp>
#include <boost/spirit/home/qi/string.hpp>
#include <boost/spirit/home/qi/char.hpp>

#include <boost/spirit/home/qi/numeric/uint.hpp>
#include <boost/spirit/home/qi/numeric/int.hpp>

#include <boost/spirit/include/karma.hpp>

#include <boost/iterator/function_input_iterator.hpp>

#include <boost/spirit/repository/home/qi/numeric/numeric.hpp>

#include <boost/mpl/x11/map.hpp>

#include <boost/random/random_device.hpp>

namespace qi = boost::spirit::qi;
namespace karma = boost::spirit::karma;
namespace qi_repo = boost::spirit::repository::qi;

namespace x11 = boost::mpl::x11;

template <typename T>
void make_numbers(
	std::vector<T> &out, size_t count,
	std::basic_string<T> const &delim
)
{
	using karma::uint_;
	using karma::lit;

	boost::random_device r;

	karma::generate(
		std::back_inserter(out),
		uint_ % lit(delim),
		boost::make_iterator_range(
			boost::make_function_input_iterator(r, size_t(0)),
			boost::make_function_input_iterator(r, count)
		)
	);
}

struct to_decimal {
	bool operator()(char const &in, boost::optional<char> &out)
	{
		printf("map %c, %c\n", in, *out);
		if ((in & 0xf0) == 0x30) {
			out = in & 0xf;
			return true;
		} else
			return false;
	}
};

template <typename T>
void test_vector(std::vector<T> &out, std::vector<char> const &in)
{
	using boost::spirit::standard::digit_type;
	using boost::spirit::standard::space_type;

	typedef x11::map<
		x11::pair<qi_repo::with_extractor, digit_type>,
		x11::pair<
			qi_repo::with_inserter,
			qi_repo::detail::default_inserter<T>
		>
	> int_policy;
	qi_repo::numeric_parser<T, int_policy> uint1;

	qi::rule<
		std::vector<char>::const_iterator, std::vector<T>(), space_type
	> p(uint1 % ',');

	bool rv(qi::phrase_parse(in.begin(), in.end(), p, space_type(), out));
}

template <typename T>
void test_vector_ref(std::vector<T> &out, std::vector<char> const &in)
{
	using boost::spirit::standard::space_type;
	using qi::uint_;

	qi::rule<
		std::vector<char>::const_iterator, std::vector<T>(), space_type
	> p(uint_ % ',');

	bool rv(qi::phrase_parse(in.begin(), in.end(), p, space_type(), out));
}

int main(int argc, char **argv)
{
	using karma::uint_;
	using karma::lit;

	int count(5);

	std::vector<char> rnd_str;
	make_numbers(rnd_str, count, std::string(", "));

	std::vector<unsigned int> res1, res2;
	res1.reserve(count);
	res2.reserve(count);

	test_vector<unsigned int>(res1, rnd_str);
	test_vector_ref<unsigned int>(res2, rnd_str);
	rnd_str.push_back(0);
	std::cout << "in: " << &rnd_str.front() << '\n';
	karma::generate(
		std::ostream_iterator<char>(std::cout),
		lit("o1: ") << (uint_ % lit(", ")) << lit('\n'),
		res1
	);

	karma::generate(
		std::ostream_iterator<char>(std::cout),
		lit("o2: ") << (uint_ % lit(", ")) << lit('\n'),
		res2
	);

	return 0;
}
