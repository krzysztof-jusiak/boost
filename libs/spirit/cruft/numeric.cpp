#include <cstdio>
#include <vector>

#include <boost/spirit/home/qi/nonterminal.hpp>
#include <boost/spirit/home/qi/operator.hpp>
#include <boost/spirit/home/qi/string.hpp>

#include <boost/spirit/repository/home/qi/numeric/numeric.hpp>

#include <boost/mpl/x11/map.hpp>

namespace qi = boost::spirit::qi;
namespace qi_repo = boost::spirit::repository::qi;

namespace x11 = boost::mpl::x11;

struct decimal_digit {
};

struct positional {
};

struct ascii_to_decimal {
};

int main(int argc, char **argv)
{
	std::string t_str("1 2 3 4 5");
	std::vector<int> res;
	typedef x11::map<
		x11::pair<qi_repo::with_extractor, decimal_digit>,
		x11::pair<qi_repo::with_inserter, positional>,
		x11::pair<qi_repo::with_mapper, ascii_to_decimal>
	> int_policy;
	qi_repo::numeric_parser<int, int_policy> uint1;

	qi::rule<std::string::iterator, std::vector<double>()> p(
		uint1 % ", "
	);

	bool rv(qi::parse(t_str.begin(), t_str.end(), p, res));

	size_t cnt;
	printf("rv %d, ", rv);
	for (cnt = 0; (cnt + 1) < res.size(); ++cnt)
		printf("%d, ", res[cnt]);

	if (!res.empty())
		printf("%d\n", res[cnt]);
	return 0;
}
