#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

#if defined(X11)
#include <boost/mpl/x11/set.hpp>

using namespace boost::mpl::x11;
#else
#include <boost/mpl/set.hpp>
#include <boost/mpl/set_c.hpp>
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
	//typedef set_c<char, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'>::type s2;
	typedef set<char, int, long, short> s2;

	typedef begin<s2>::type first2;
	typedef end<s2>::type last2;

	typedef distance<first2, last2> d;
	std::cout << "1: " << demangle<first2>() << '\n';
	std::cout << "1.1: " << demangle<next<first2>::type>() << '\n';
	std::cout << "2: " << demangle<last2>() << '\n';

	return 0;
}
