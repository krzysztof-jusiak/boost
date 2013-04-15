#if !defined(MPL_X11_TEST_DATA_TYPES_APR_15_2013_1310)
#define MPL_X11_TEST_DATA_TYPES_APR_15_2013_1310

#include <boost/noncopyable.hpp>

namespace boost { namespace mpl { namespace x11 { namespace test {

struct UDT {};

typedef int UDT::* mem_ptr;
typedef int (UDT::* mem_fun_ptr)();

struct incomplete;

class abstract {
	public: virtual ~abstract() = 0;
};

using boost::noncopyable;

}}}}

#endif
