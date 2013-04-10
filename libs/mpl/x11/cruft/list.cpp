#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

#if defined(X11)
#include <boost/mpl/x11/map.hpp>
#include <boost/mpl/x11/begin_end.hpp>
#include <boost/mpl/x11/clear.hpp>
#include <boost/mpl/x11/contains.hpp>
#include <boost/mpl/x11/erase.hpp>
#include <boost/mpl/x11/has_key.hpp>
#include <boost/mpl/x11/insert.hpp>
#include <boost/mpl/x11/order.hpp>
#include <boost/mpl/x11/size.hpp>
#include <boost/mpl/x11/at.hpp>

using namespace boost::mpl::x11;
#else
#include <boost/mpl/map.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/erase_key.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/order.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/empty.hpp>
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



int main(int argc, char **argv)
{

	typedef map<
		pair<int, unsigned>,
		pair<char, unsigned char>
	> m_;

	typedef erase_key<m_, char>::type m;
	std::cout << "1: " << demangle<m>() << '\n';

	typedef insert<m, pair<char, long>>::type m1;
	std::cout << "2: " << demangle<m1>() << '\n';

	typedef erase_key<m1, char>::type m_1;
	std::cout << "3: " << demangle<m_1>() << '\n';

	return 0;
}
