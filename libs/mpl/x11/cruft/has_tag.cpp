#include <cstdio>

#include <boost/mpl/x11/detail/has_tag.hpp>
#include <boost/mpl/x11/arithmetic.hpp>
//#include <boost/mpl/x11/size.hpp>
//#include <boost/mpl/x11/empty.hpp>

using namespace boost::mpl::x11;

struct aaa_tag;
struct bbb_tag;

struct aaa {
	typedef aaa_tag tag;
};

struct bbb {
	typedef bbb_tag tag;
};

int main(int argc, char **argv)
{
	typedef detail::has_tag<aaa> t0;
	typedef detail::has_tag<bbb> t1;
	typedef x11::int_<10> _10;

	printf("x: %d, %d\n", t0::value, t1::value);
	printf("x: %d\n", plus<_10, _10, _10, _10>::value);
	//printf("%ld\n", size<l1>::value);
	//printf("%ld\n", size<l2>::value);
	//printf("%ld\n", size<l9>::value);
	return 0;
}
