#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

#define X11 1

#if defined(X11)
#include <boost/mpl/x11/reverse_fold.hpp>
#include <boost/mpl/x11/comparison.hpp>
#include <boost/mpl/x11/push_pop.hpp>
#include <boost/mpl/x11/remove.hpp>
#include <boost/mpl/x11/equal.hpp>
#include <boost/mpl/x11/copy.hpp>
#include <boost/mpl/x11/size.hpp>
#include <boost/mpl/x11/vector.hpp>

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
{
	typedef vector_c<int, 5, -1, 0, -7, -2, 0, -5, 4> numbers;
	typedef vector_c<int, -1, -7, -2, -5> negatives;
	typedef reverse_fold<
		numbers, vector_c<int>, if_<
			less<arg<1>, int_<0>>, push_front<arg<0>, arg<1>>,
			arg<0>
	>>::type result;

	typedef detail::equal_impl<
		result, negatives, equal_to<arg<0>, arg<1>>
	> t1;
	
	std::cout << "x11: " << demangle<result>() << "\n\n";
	std::cout << "x12: " << demangle<t1>() << "\n\n";
	std::cout << "x13: " << demangle<deref<next<typename t1::first1_>>::type>() << "\n\n";
	std::cout << "x14: " << demangle<deref<next<typename t1::first2_>>::type>() << "\n\n";

	std::cout << "v11: "
		  << equal<result, negatives, equal_to<arg<0>, arg<1>>>::value
		  << '\n';

}
{
	typedef vector_c<int, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9>::type numbers;
	typedef vector_c<int, 4, 3, 2, 1, 0>::type answer;
	typedef copy_if<
		numbers, less<arg<-1>, int_<5>>, front_inserter<vector_c<int>>
	>::type result;

	std::cout << "v21: " << size<result>::value << '\n';
	std::cout << "v22: " << equal<result, answer>::value << '\n';
}
{
	typedef vector_c<int, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9> numbers;
	typedef vector_c<int, 4, 3, 2, 1, 0>::type answer;
	typedef remove_if<
		numbers, greater<arg<-1>, int_<4>>, front_inserter<vector_c<int>>
	>::type result;

	std::cout << "v31: " << size<result>::value << '\n';
	std::cout << "v32: " << equal<result, answer>::value << '\n';
}
	return 0;
}
