/*==============================================================================
    Copyright (c) 2009      Eric Niebler
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/string.hpp>
#include <boost/mpl/x11/size.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace test {

template<char const *sz>
struct greeting {
	std::string say_hello() const
	{
		return sz;
	}
};

struct push_char {
	push_char(std::string &str) : str_(&str) {}

	void operator()(char ch) const
	{
		this->str_->push_back(ch);
	}

	std::string *str_;
};

}

BOOST_AUTO_TEST_CASE(string_0)
{
	typedef string<
		'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa',
		'aaa'
	> almost_full;

        typedef string<
		'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa',
		'aaaa'
	> full;

	BOOST_CHECK_EQUAL(0, (size<string<>>::value));
	BOOST_CHECK_EQUAL(1, (size<string<'a'>>::value));
	BOOST_CHECK_EQUAL(2, (size<string<'ab'>>::value));
	BOOST_CHECK_EQUAL(2, (size<string<'a', 'b'>>::value));
	BOOST_CHECK_EQUAL(4, (size<string<'abcd'>>::value));
	BOOST_CHECK_EQUAL(5, (size<string<'abcd', 'e'>>::value));
	BOOST_CHECK_EQUAL(31, (size<almost_full>::value));
	BOOST_CHECK_EQUAL(32, (size<full>::value));
}

BOOST_AUTO_TEST_CASE(string_1)
{
	using detail::string_iterator;

	typedef string<
		'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa',
		'aaa'
	> almost_full;

        typedef string<
		'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa',
		'aaaa'
	> full;

	BOOST_CHECK((std::is_same<                                           \
		begin<string<>>::type, end<string<>>::type                   \
	>::value));
	BOOST_CHECK((std::is_same<                                           \
		begin<string<'a'>>::type, string_iterator<string<'a'>, 0, 0> \
	>::value));
	BOOST_CHECK((std::is_same< \
		end<string<'a'>>::type, string_iterator<string<'a'>, 1, 0>   \
	>::value));
	BOOST_CHECK((std::is_same<                                           \
		begin<almost_full>::type, string_iterator<almost_full, 0, 0> \
	>::value));
	BOOST_CHECK((std::is_same<                                           \
		end<almost_full>::type, string_iterator<almost_full, 8, 0>   \
	>::value));
	BOOST_CHECK((std::is_same<                                           \
		begin<full>::type, string_iterator<full, 0, 0>               \
	>::value));
	BOOST_CHECK((std::is_same<                                           \
		end<full>::type, string_iterator<full, 8, 0>                 \
	>::value));
}
#if 0
BOOST_AUTO_TEST_CASE(string_2)
{
	typedef push_back<string<>, char_<'a'>>::type t1;
	BOOST_CHECK((std::is_same<t1, string<'a'>>::value));

	typedef push_back<t1, char_<'b'>>::type t2;
	BOOST_CHECK((std::is_same<t2, string<'ab'>>::value));

	typedef push_back<t2, char_<'c'>>::type t3;
	BOOST_CHECK((std::is_same<t3, string<'abc'>>::value));

	typedef push_back<t3, char_<'d'>>::type t4;
	BOOST_CHECK((std::is_same<t4, string<'abcd'>>::value));

	typedef push_back<t4, char_<'e'>>::type t5;
	BOOST_CHECK((std::is_same<t5, string<'abcd', 'e'>>::value));

	typedef string<
		'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaa'
	> almost_full;

	typedef push_back<almost_full, char_<'X'>>::type t6;
	BOOST_CHECK((std::is_same<t6, string<                                  \
		'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaX' \
	>>::value));
}

BOOST_AUTO_TEST_CASE(string_3)
{
	typedef string<'a', 'bc', 'def', 'ghij'> s;

	typedef begin<s>::type i0;
	BOOST_CHECK((std::is_same<i0, string_iterator<s, 0, 0>>::value));

	typedef next<i0>::type i1;
	BOOST_CHECK((std::is_same<i1, string_iterator<s, 1, 0>>::value));

	typedef next<i1>::type i2;
	BOOST_CHECK((std::is_same<i2, string_iterator<s, 1, 1>>::value));

	typedef next<i2>::type i3;
	BOOST_CHECK((std::is_same<i3, string_iterator<s, 2, 0>>::value));

	typedef next<i3>::type i4;
	BOOST_CHECK((std::is_same<i4, string_iterator<s, 2, 1>>::value));

	typedef next<i4>::type i5;
	BOOST_CHECK((std::is_same<i5, string_iterator<s, 2, 2>>::value));

	typedef next<i5>::type i6;
	BOOST_CHECK((std::is_same<i6, string_iterator<s, 3, 0>>::value));

	typedef next<i6>::type i7;
	BOOST_CHECK((std::is_same<i7, string_iterator<s, 3, 1>>::value));

	typedef next<i7>::type i8;
	BOOST_CHECK((std::is_same<i8, string_iterator<s, 3, 2>>::value));

	typedef next<i8>::type i9;
	BOOST_CHECK((std::is_same<i9, string_iterator<s, 3, 3>>::value));

	typedef next<i9>::type i10;
	BOOST_CHECK((std::is_same<i10, string_iterator<s, 4, 0>>::value));

	BOOST_CHECK((std::is_same<i10, end<s>::type>::value));
}

BOOST_AUTO_TEST_CASE(string_4)
{
	typedef string<'a', 'bc', 'def', 'ghij'> s;

	typedef end<s>::type i10;
	BOOST_CHECK((std::is_same<i10, string_iterator<s, 4, 0>>::value));

	typedef prior<i10>::type i9;
	BOOST_CHECK((std::is_same<i9, string_iterator<s, 3, 3>>::value));

	typedef prior<i9>::type i8;
	BOOST_CHECK((std::is_same<i8, string_iterator<s, 3, 2>>::value));

	typedef prior<i8>::type i7;
	BOOST_CHECK((std::is_same<i7, string_iterator<s, 3, 1>>::value));

	typedef prior<i7>::type i6;
	BOOST_CHECK((std::is_same<i6, string_iterator<s, 3, 0>>::value));

	typedef prior<i6>::type i5;
	BOOST_CHECK((std::is_same<i5, string_iterator<s, 2, 2>>::value));

	typedef prior<i5>::type i4;
	BOOST_CHECK((std::is_same<i4, string_iterator<s, 2, 1>>::value));

	typedef prior<i4>::type i3;
	BOOST_CHECK((std::is_same<i3, string_iterator<s, 2, 0>>::value));

	typedef prior<i3>::type i2;
	BOOST_CHECK((std::is_same<i2, string_iterator<s, 1, 1>>::value));

	typedef prior<i2>::type i1;
	BOOST_CHECK((std::is_same<i1, string_iterator<s, 1, 0>>::value));

	typedef prior<i1>::type i0;
	BOOST_CHECK((std::is_same<i0, string_iterator<s, 0, 0>>::value));

	BOOST_CHECK((std::is_same<i0, begin<s>::type>::value));
}

BOOST_AUTO_TEST_CASE(string_5)
{
	typedef string<'a', 'bc', 'def', 'ghij'> s;

	typedef begin<s>::type i0;
	BOOST_CHECK((std::is_same<deref<i0>::type, char_<'a'>>::value));

	typedef next<i0>::type i1;
	BOOST_CHECK((std::is_same<deref<i1>::type, char_<'b'>>::value));

	typedef next<i1>::type i2;
	BOOST_CHECK((std::is_same<deref<i2>::type, char_<'c'>>::value));

	typedef next<i2>::type i3;
	BOOST_CHECK((std::is_same<deref<i3>::type, char_<'d'>>::value));

	typedef next<i3>::type i4;
	BOOST_CHECK((std::is_same<deref<i4>::type, char_<'e'>>::value));

	typedef next<i4>::type i5;
	BOOST_CHECK((std::is_same<deref<i5>::type, char_<'f'>>::value));

	typedef next<i5>::type i6;
	BOOST_CHECK((std::is_same<deref<i6>::type, char_<'g'>>::value));

	typedef next<i6>::type i7;
	BOOST_CHECK((std::is_same<deref<i7>::type, char_<'h'>>::value));

	typedef next<i7>::type i8;
	BOOST_CHECK((std::is_same<deref<i8>::type, char_<'i'>>::value));

	typedef next<i8>::type i9;
	BOOST_CHECK((std::is_same<deref<i9>::type, char_<'j'>>::value));
}

BOOST_AUTO_TEST_CASE(string_6)
{
	typedef push_back<string<>, char_<'a'>>::type t1;
	BOOST_CHECK((std::is_same<t1, string<'a'>>::value));

	typedef push_back<t1, char_<'b'>>::type t2;
	BOOST_CHECK((std::is_same<t2, string<'ab'>>::value));

	typedef push_back<t2, char_<'c'>>::type t3;
	BOOST_CHECK((std::is_same<t3, string<'abc'>>::value));

	typedef push_back<t3, char_<'d'>>::type t4;
	BOOST_CHECK((std::is_same<t4, string<'abcd'>>::value));

	typedef push_back<t4, char_<'e'>>::type t5;
	BOOST_CHECK((std::is_same<t5, string<'abcd','e'>>::value));

	typedef string<
		'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaa'
	> almost_full;
	typedef push_back<almost_full, char_<'X'>>::type t6;
	BOOST_CHECK((std::is_same<t6, string<                                  \
		'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaX' \
	>>::value));

	typedef string<'a', 'a', 'a', 'a', 'a', 'a', 'a', 'aaaa'> must_repack;
	typedef push_back<must_repack, char_<'X'>>::type t7;
	BOOST_CHECK((std::is_same<t7, string<'aaaa', 'aaaa', 'aaaX'>>::value));
}

BOOST_AUTO_TEST_CASE(string_7)
{
	BOOST_CHECK((empty<string<>>::value));
	BOOST_CHECK(!(empty<string<'hi!'>>::value));
}

BOOST_AUTO_TEST_CASE(string_8)
{
	typedef push_front<string<>, char_<'a'>>::type t1;
	BOOST_CHECK((std::is_same<t1, string<'a'>>::value));

	typedef push_front<t1, char_<'b'>>::type t2;
	BOOST_CHECK((std::is_same<t2, string<'ba'>>::value));

	typedef push_front<t2, char_<'c'>>::type t3;
	BOOST_CHECK((std::is_same<t3, string<'cba'>>::value));

	typedef push_front<t3, char_<'d'>>::type t4;
	BOOST_CHECK((std::is_same<t4, string<'dcba'>>::value));

	typedef push_front<t4, char_<'e'>>::type t5;
	BOOST_CHECK((std::is_same<t5, string<'e','dcba'>>::value));

	typedef string<
		'aaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa'
	> almost_full;
	typedef push_front<almost_full, char_<'X'>>::type t6;
	BOOST_CHECK((std::is_same<t6, string<                                  \
		'Xaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa' \
	>>::value));

	typedef string<'aaaa','a','a','a','a','a','a','a'> must_repack;
	typedef push_front<must_repack, char_<'X'>>::type t7;
	BOOST_CHECK((std::is_same<t7, string<'Xaaa', 'aaaa', 'aaaa'>>::value));
}

BOOST_AUTO_TEST_CASE(string_9)
{
	BOOST_CHECK_EQUAL(0, std::strcmp(c_str<string<>>::value, ""));

	BOOST_CHECK_EQUAL(0, std::strcmp(                               \
		c_str<string<'Hell', 'o wo', 'rld!'>>::value,           \
		"Hell" "o wo" "rld!"                                    \
	));

	BOOST_CHECK_EQUAL(0, std::strcmp(                               \
		c_str<string<                                           \
			'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', \
			'aaaa', 'aaaX'                                  \
		>>::value,                                              \
		"aaaa" "aaaa" "aaaa" "aaaa" "aaaa" "aaaa" "aaaa" "aaaX" \
	));

	greeting<c_str<string<'Hell', 'o wo', 'rld!'>>::value> g;
	BOOST_CHECK_EQUAL("Hello world!", g.say_hello());

	std::string result;
	for_each<string<'Hell', 'o wo', 'rld!'>>(push_char(result));
	BOOST_CHECK_EQUAL("Hello world!", result);

	BOOST_CHECK_EQUAL(('h', front<string<'hi!'>>::type()));
	BOOST_CHECK_EQUAL(('!', back<string<'hi!'>>::type()));

	typedef vector_c<char, 'a', 'b', 'c', 'd', 'e'> rgc;
	BOOST_CHECK_EQUAL(0, std::strcmp("abcde", c_str<rgc>::value));

	typedef copy<rgc, back_inserter<string<>>>::type str;
	BOOST_CHECK_EQUAL(0, std::strcmp("abcde", c_str<str>::value));
}

BOOST_AUTO_TEST_CASE(string_10)
{
	typedef string<'Hell', 'o wo', 'rld!'> hello;
	typedef advance_c<begin<hello>::type, 5>::type where;
	typedef string<' cru', 'el'> cruel;
	typedef insert_range<hello, where, cruel>::type hello_cruel;
	BOOST_CHECK_EQUAL(0, (std::strcmp(                      \
		"Hello cruel world!", c_str<hello_cruel>::value \
	)));

	typedef erase<hello, begin<hello>::type, where>::type erased1;
	BOOST_CHECK_EQUAL(0, std::strcmp(" world!", c_str<erased1>::value));
}

BOOST_AUTO_TEST_CASE(string_11)
{
	 BOOST_CHECK((std::is_same<                                     \
		pop_front<string<'a'>>::type, string<>                  \
	>::value));

	BOOST_CHECK((std::is_same<                                      \
		pop_front<string<'ab'>>::type, string<'b'>              \
	>::value));

	BOOST_CHECK((std::is_same<                                      \
		pop_front<string<'abc'>>::type, string<'bc'>            \
	>::value));

	BOOST_CHECK((std::is_same<                                      \
		pop_front<string<'abcd'>>::type, string<'bcd'>          \
	>::value));

	BOOST_CHECK((std::is_same<                                      \
		pop_front<string<'abcd', 'e'>>::type, string<'bcd','e'>  \
	>::value));

	BOOST_CHECK((std::is_same<                                      \
		pop_front<string<'d', 'e'>>::type, string<'e'>           \
	>::value));

	BOOST_CHECK((std::is_same<                                      \
		pop_front<string<                                       \
			'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', \
			'aaaa', 'aaaa'                                  \
		>>::type, string<                                       \
			'aaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa',  \
			'aaaa', 'aaaa'                                  \
		>                                                       \
	>::value));
}

BOOST_AUTO_TEST_CASE(string_12)
{
	 BOOST_CHECK((std::is_same<                                     \
		pop_back<string<'a'>>::type, string<>                   \
	>::value));

	BOOST_CHECK((std::is_same<                                      \
		pop_back<string<'ab'>>::type, string<'a'>               \
	>::value));

	BOOST_CHECK((std::is_same<                                      \
		pop_back<string<'abc'>>::type, string<'ab'>             \
	>::value));

	BOOST_CHECK((std::is_same<                                      \
		pop_back<string<'abcd'>>::type, string<'abc'>           \
	>::value));

	BOOST_CHECK((std::is_same<                                      \
		pop_back<string<'abcd','e'>>::type, string<'abcd'>      \
	>::value));

	BOOST_CHECK((std::is_same<                                      \
		pop_back<string<'d','e'>>::type, string<'d'>            \
	>::value));

	BOOST_CHECK((std::is_same<                                      \
		pop_back<string<                                        \
			'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', \
			'aaaa', 'aaaa'                                  \
		>>::type, string<                                       \
			'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', 'aaaa', \
			'aaaa', 'aaa'                                   \
		>                                                       \
	>::value));
}

BOOST_AUTO_TEST_CASE(string_13)
{
	BOOST_CHECK_EQUAL((at_c<string<'\x7f'>, 0>::type::value), char(0x7f));

	BOOST_CHECK_EQUAL((at_c<string<'\x80'>, 0>::type::value), char(0x80));

	BOOST_CHECK_EQUAL(                                              \
		(at_c<                                                  \
			string<at_c<string<'\x7f'>, 0>::type::value>, 0 \
		>::type::value), char(0x7f)                             \
	);

	BOOST_CHECK_EQUAL(                                              \
		(at_c<                                                  \
			string<at_c<string<'\x80'>, 0>::type::value>, 0 \
		>::type::value), char(0x80)                             \
	);
}
#endif
}}}
