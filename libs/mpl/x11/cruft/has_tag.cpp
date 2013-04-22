#include <cstdio>

#include <boost/mpl/x11/detail/has_tag.hpp>
#include <boost/mpl/x11/arithmetic.hpp>
#include <boost/mpl/x11/transform_view.hpp>
#include <boost/mpl/x11/equal.hpp>
#include <boost/mpl/x11/zip_view.hpp>
#include <boost/mpl/x11/vector.hpp>
#include <boost/mpl/x11/range_c.hpp>
#include <boost/mpl/x11/unpack_args.hpp>
#include <boost/mpl/x11/filter_view.hpp>
#include <boost/mpl/x11/is_even.hpp>

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
	typedef int_<10> _10;

	typedef transform_view<
		zip_view<
			vector<
				range_c<int, 0, 10>, range_c<int, 10, 20>
			>
		>, unpack_args<plus<>>
	> result;
	typedef typename equal<
		result,
		filter_view<
			range_c<int, 10, 30>,
			is_even<arg<-1>>
		>,
		equal_to<arg<-1>, arg<-1>>
	>::type x1;

	printf("x: %d, %d\n", t0::value, t1::value);
	printf("x: %d\n", plus<_10, _10, _10, _10>::value);
	//printf("%ld\n", size<l1>::value);
	//printf("%ld\n", size<l2>::value);
	//printf("%ld\n", size<l9>::value);
	return 0;
}
