#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

#define X11 1

#if defined(X11)
#include <boost/mpl/x11/apply.hpp>
#include <boost/mpl/x11/arithmetic.hpp>

using namespace boost::mpl::x11;

#else
#include <boost/mpl/apply.hpp>

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

int main(int argc, char **argv)
{
	typedef apply<lambda<arg<0>>, plus<arg<0>, arg<1>>>::type plus_fun;
	typedef apply_wrap<plus_fun, int_<2>, int_<3>>::type res;

	std::cout << "1.1: " << demangle<plus_fun>() << "\n\n";
	std::cout << "1.2: " << demangle<res>() << "\n\n";

	typedef typename lambda<lambda<arg<0>>>::type le;
	typedef apply_wrap<le, plus<arg<0>, arg<1>>> le1;
	typedef typename le::template apply<plus<arg<0>, arg<1>>> le2;
	std::cout << "2.1: " << demangle<le>() << "\n\n";
	std::cout << "2.2: " << demangle<le1>() << "\n\n";
	std::cout << "2.3: " << demangle<le2>() << "\n\n";
	return 0;
}
