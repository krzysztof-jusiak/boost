#include <cstdio>
#include <typeinfo>

#include <boost/mpl/x11/map.hpp>
#include <boost/mpl/x11/begin_end.hpp>
#include <boost/mpl/x11/clear.hpp>
#include <boost/mpl/x11/contains.hpp>
#include <boost/mpl/x11/erase.hpp>
#include <boost/mpl/x11/has_key.hpp>
#include <boost/mpl/x11/insert.hpp>
#include <boost/mpl/x11/order.hpp>
#include <boost/mpl/x11/size.hpp>


using namespace boost::mpl::x11;

int main(int argc, char **argv)
{

	typedef map<
		pair<int, unsigned>,
		pair<char, unsigned char>
	> m0;

	printf("%s\n", typeid(m0).name());

	typedef erase_key<m_, char>::type m1;

	printf("%s\n", typeid(m1).name());

	typedef insert<m1, pair<char, long>>::type m2;
	printf("%s\n", typeid(m2).name());

	typedef insert<m2, pair<short, unsigned>>::type m3;
	printf("%s\n", typeid(m3).name());

	return 0;
}
