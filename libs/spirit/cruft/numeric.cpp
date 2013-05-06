#include <cstdio>
#include <vector>

#include <boost/spirit/home/qi/nonterminal.hpp>
#include <boost/spirit/home/qi/operator.hpp>
#include <boost/spirit/home/qi/string.hpp>
#include <boost/spirit/home/qi/char.hpp>

#include <boost/spirit/repository/home/qi/numeric/numeric.hpp>

#include <boost/mpl/x11/map.hpp>

namespace qi = boost::spirit::qi;
namespace qi_repo = boost::spirit::repository::qi;

namespace x11 = boost::mpl::x11;

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

int main(int argc, char **argv)
{
	using boost::spirit::standard::digit_type;
	using boost::spirit::standard::space_type;
	using boost::spirit::standard::space;

	std::string t_str("123, 12345, 45678, 3, 4, 5");
	std::vector<int> res;
	typedef x11::map<
		x11::pair<qi_repo::with_extractor, digit_type>,
		x11::pair<
			qi_repo::with_inserter,
			qi_repo::detail::default_inserter<int>
		>//,
//		x11::pair<qi_repo::with_filter, to_decimal>
	> int_policy;
	qi_repo::numeric_parser<int, int_policy> uint1;

	qi::rule<std::string::iterator, std::vector<int>(), space_type> p(
		uint1 % ','
	);

	bool rv(qi::phrase_parse(t_str.begin(), t_str.end(), p, space, res));

	size_t cnt;
	printf("rv %d, ", rv);
	for (cnt = 0; (cnt + 1) < res.size(); ++cnt)
		printf("%d, ", res[cnt]);

	if (!res.empty())
		printf("%d\n", res[cnt]);
	return 0;
}
