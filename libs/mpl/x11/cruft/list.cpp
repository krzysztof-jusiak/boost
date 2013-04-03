#include <cstdio>

#include <boost/mpl/x11/list.hpp>
#include <boost/mpl/x11/size.hpp>
//#include <boost/mpl/x11/empty.hpp>

using namespace boost::mpl::x11;

int main(int argc, char **argv)
{
	typedef list<> l0;
	typedef list<char> l1;
	typedef list<char, long> l2;
	typedef list<char, char, char, char, char, char, char, char, char> l9;

	printf("%ld\n", size<l0>::value);
	printf("%ld\n", size<l1>::value);
	printf("%ld\n", size<l2>::value);
	printf("%ld\n", size<l9>::value);
	return 0;
}
