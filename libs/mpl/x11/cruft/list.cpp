#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

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

template <typename T>
std::string demangle()
{
	auto *s(abi::__cxa_demangle(typeid(T).name(), 0, 0, 0));
	std::string rv(s);
	free(s);
	return rv;
}

using namespace boost::mpl::x11;

int main(int argc, char **argv)
{

	typedef map<
		pair<int, unsigned>,
		pair<char, unsigned char>,
		pair<short, long>
	> m1;

	//std::cout << demangle<m0>() << '\n';

	//typedef erase_key<m0, char>::type m1;

	//std::cout << demangle<deref<begin<m1>>::type>() << '\n';

	typedef insert<m1, pair<char, long>>::type m2;
	std::cout << "1: " << demangle<m2>() << '\n';
//	std::cout << "2: " << demangle<m2::t1>() << '\n';
//	std::cout << "2.1: " << demangle<m2::t1::x_tag>() << '\n';
//	std::cout << "3: " << demangle<m2::t2>() << '\n';
//	std::cout << "3.1: " << demangle<m2::t2::x_tag>() << '\n';
//	std::cout << "3.1: " << demangle<m2::t2::y_tag>() << '\n';
//	std::cout << "4: "<< demangle<m2::type>() << '\n';
	//typedef detail::insert_impl<typename sequence_tag<m1>::type> tm2;
	//std::cout << demangle<tm2>() << '\n';

	typedef insert<m2, pair<short, unsigned>>::type m3;
	std::cout << demangle<m3>() << '\n';

	return 0;
}
