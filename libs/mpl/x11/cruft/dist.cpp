#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

#if defined(X11)
#include <boost/mpl/x11/set.hpp>
#include <boost/mpl/x11/list.hpp>
#include <boost/mpl/x11/find.hpp>
#include <boost/mpl/x11/erase.hpp>
#include <boost/mpl/x11/size.hpp>

using namespace boost::mpl::x11;

#else
#include <boost/mpl/set.hpp>
#include <boost/mpl/set_c.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/begin_end.hpp>

using namespace boost::mpl;

#endif

template <typename T>
std::string demangle()
{
	auto *s(abi::__cxa_demangle(typeid(T).name(), 0, 0, 0));
	std::string rv(s);
	free(s);
	return rv;
}

template <typename T>
struct std_vector {};

int main(int argc, char **argv)
{
	//typedef set_c<char, 'a'>::type s2;
	typedef set_c<char, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'>::type s2;

	typedef begin<s2>::type first2;
	typedef end<s2>::type last2;

	typedef has_key<s2, char> y;
	typedef has_key<s2, int> n;
	typedef distance<first2, last2> d;
	std::cout << "1.1: " << demangle<s2>() << "\n\n";
	std::cout << "1.2: " << demangle<first2>() << "\n\n";
	std::cout << "1.3: " << demangle<next<first2>::type>() << "\n\n";
	std::cout << "2.1: " << demangle<y::type>() << "\n\n";
	std::cout << "2.2: " << demangle<n::type>() << "\n\n";
	std::cout << "3.1: " << demangle<d::type>() << "\n\n";

	typedef list<int, char, long, short, char, long, double, long> types;
	typedef find<types, short>::type iter;

	typedef erase<types, iter>::type result;
	std::cout << "4.1: " << demangle<result>() << "\n\n";

	return 0;
}
