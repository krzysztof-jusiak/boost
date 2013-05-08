#include <cstdio>
#include <vector>

#include <boost/spirit/home/qi/nonterminal.hpp>
#include <boost/spirit/home/qi/operator.hpp>
#include <boost/spirit/home/qi/string.hpp>
#include <boost/spirit/home/qi/char.hpp>

#include <boost/spirit/home/qi/numeric/uint.hpp>
#include <boost/spirit/home/qi/numeric/int.hpp>

#include <boost/spirit/repository/home/qi/numeric/numeric.hpp>

#include <boost/mpl/x11/map.hpp>

#include <boost/random/random_device.hpp>

namespace qi = boost::spirit::qi;
namespace qi_repo = boost::spirit::repository::qi;

namespace x11 = boost::mpl::x11;

template <typename T>
void make_numbers(
	std::vector<T> &out, size_t count, unsigned int min_digits,
	unsigned int max_digits, std::basic_string<T> const &delim
)
{
	std::vector<T> single(max_digits);
	boost::random_device r;
	int c_dig(0);

	for (size_t c(0); c < count; ++c) {
		single.clear();

		for (int d(0); d < max_digits; ++d) {
			int x(r());
			if (10 > (x & 0xf))
				
		}
	}
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
void test_vector(std::string s)
{
	using boost::spirit::standard::digit_type;
	using boost::spirit::standard::space_type;

	std::vector<T> res;
	typedef x11::map<
		x11::pair<qi_repo::with_extractor, digit_type>,
		x11::pair<
			qi_repo::with_inserter,
			qi_repo::detail::default_inserter<T>
		>//,
//		x11::pair<qi_repo::with_filter, to_decimal>
	> int_policy;
	qi_repo::numeric_parser<T, int_policy> uint1;

	qi::rule<std::string::iterator, std::vector<T>(), space_type> p(
		uint1 % ','
		//boost::spirit::ushort_ % ','
	);

	bool rv(qi::phrase_parse(s.begin(), s.end(), p, space_type(), res));

	std::cout << typeid(T).name() << ": rv: " << rv << '\n';
	bool delim(false);
	for(T const &v: res) {
		if (delim)
			std::cout << ", ";

		delim = true;
		std::cout << long(v);
	}
	std::cout << '\n';
}

int main(int argc, char **argv)
{
	std::string t_str("30000, 32767, 32768, 32769, 65535, 65536, 65537");
	test_vector<char>(t_str);
	test_vector<unsigned char>(t_str);
	test_vector<short>(t_str);
	test_vector<unsigned short>(t_str);

	return 0;
}
