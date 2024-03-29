/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2001-2011 Hartmut Kaiser
    Copyright (c) 2011      Bryce Lelbach
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE spirit
#include <boost/test/included/unit_test.hpp>

#include <boost/any.hpp>
#include <boost/mpl/x11/insert.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/repository/home/qi/numeric/uint.hpp>

#include "test.hpp"

namespace boost { namespace spirit { namespace repository { namespace qi {
namespace test {

char const *max_unsigned = "4294967295";
char const *unsigned_overflow = "4294967296";

char const *max_int = "2147483647";
char const *int_overflow = "2147483648";
char const *min_int = "-2147483648";
char const *int_underflow = "-2147483649";

char const *max_binary = "11111111111111111111111111111111";
char const *binary_overflow = "100000000000000000000000000000000";

char const *max_octal = "37777777777";
char const *octal_overflow = "100000000000";

char const *max_hex = "FFFFFFFF";
char const *hex_overflow = "100000000";

struct ts_filter {
	boost::any last_pos;
	bool first_group;

	template <typename Iterator>
	bool pre(Iterator const &iter)
	{
		last_pos = iter;
		first_group = true;
		return true;
	}

	template <typename Iterator>
	bool post(Iterator &iter)
	{
		auto last_iter(boost::any_cast<Iterator>(last_pos));
		auto count(iter - last_iter);

		return (first_group && (count <= 3)) || (count == 3);
	}

	template <typename Iterator>
	bool operator()(Iterator &first, Iterator const &last)
	{
		auto last_iter(boost::any_cast<Iterator>(last_pos));
		auto count(first - last_iter);

		switch (count) {
		case 0:
			return false;
		case 1:
		case 2:
			if (!first_group)
				return false;

			first_group = false;
		case 3:
			if (*first == ',') {
				++first;
				last_pos = first;
				return true;
			}
		default:
			return false;
		}
	}
};

}

BOOST_AUTO_TEST_CASE(uint_0)
{
	unsigned int u;

	BOOST_CHECK(test::parse("123456", uint_));
	BOOST_CHECK(test::parse_attr("123456", uint_, u));
	BOOST_CHECK_EQUAL(u, 123456);

	BOOST_CHECK(test::parse(test::max_unsigned, uint_));
	BOOST_CHECK(test::parse_attr(test::max_unsigned, uint_, u));
	BOOST_CHECK_EQUAL(u, UINT_MAX);

	BOOST_CHECK(test::parse(test::unsigned_overflow, uint_));
	BOOST_CHECK(test::parse_attr(test::unsigned_overflow, uint_, u));
	BOOST_CHECK_EQUAL(u, UINT_MAX / 10);
}

BOOST_AUTO_TEST_CASE(uint_1)
{
	unsigned int u;

	BOOST_CHECK(test::parse("11111110", bin));
	BOOST_CHECK(test::parse_attr("11111110", bin, u));
	BOOST_CHECK_EQUAL(u, 0xFE);

	BOOST_CHECK(test::parse(test::max_binary, bin));
	BOOST_CHECK(test::parse_attr(test::max_binary, bin, u));
	BOOST_CHECK_EQUAL(u, UINT_MAX);

	BOOST_CHECK(test::parse(test::binary_overflow, bin));
	BOOST_CHECK(test::parse_attr(test::binary_overflow, bin, u));
	BOOST_CHECK_EQUAL(u, 0b10000000000000000000000000000000);
}

BOOST_AUTO_TEST_CASE(uint_2)
{
	unsigned int u;

	BOOST_CHECK(test::parse("12545674515", oct));
	BOOST_CHECK(test::parse_attr("12545674515", oct, u));
	BOOST_CHECK_EQUAL(u, 012545674515);

	BOOST_CHECK(test::parse(test::max_octal, oct));
	BOOST_CHECK(test::parse_attr(test::max_octal, oct, u));
	BOOST_CHECK_EQUAL(u, UINT_MAX);

	BOOST_CHECK(test::parse(test::octal_overflow, oct));
	BOOST_CHECK(test::parse_attr(test::octal_overflow, oct, u));
	BOOST_CHECK_EQUAL(u, 010000000000);
}

BOOST_AUTO_TEST_CASE(uint_3)
{
	unsigned int u;

	BOOST_CHECK(test::parse("95BC8DF", hex));
	BOOST_CHECK(test::parse_attr("95BC8DF", hex, u));
	BOOST_CHECK_EQUAL(u, 0x95BC8DF);

	BOOST_CHECK(test::parse("abcdef12", hex));
	BOOST_CHECK(test::parse_attr("abcdef12", hex, u));
	BOOST_CHECK_EQUAL(u, 0xabcdef12);

	BOOST_CHECK(test::parse(test::max_hex, hex));
	BOOST_CHECK(test::parse_attr(test::max_hex, hex, u));
	BOOST_CHECK_EQUAL(u, UINT_MAX);

	BOOST_CHECK(test::parse(test::hex_overflow, hex));
	BOOST_CHECK(test::parse_attr(test::hex_overflow, hex, u));
	BOOST_CHECK_EQUAL(u, 0x10000000);
}

BOOST_AUTO_TEST_CASE(uint_4)
{
	unsigned int u;

	numeric_parser<unsigned int, mpl::x11::map<
		mpl::x11::pair<with_extractor, standard::digit_type>,
		mpl::x11::pair<
			with_integer,
			detail::fixed_ascii_integer<
				unsigned int, 10, 3
			>
		>,
		mpl::x11::pair<with_filter, detail::length_filter<1>>
	>> uint3;

	BOOST_CHECK(test::parse_attr("123456", uint3, u));
	BOOST_CHECK_EQUAL(u, 123);

	numeric_parser<unsigned int, mpl::x11::map<
		mpl::x11::pair<with_extractor, standard::digit_type>,
		mpl::x11::pair<
			with_integer,
			detail::fixed_ascii_integer<
				unsigned int, 10, 4
			>
		>,
		mpl::x11::pair<with_filter, detail::length_filter<2>>
	>> uint4;

	BOOST_CHECK(test::parse_attr("123456", uint4, u));
	BOOST_CHECK_EQUAL(u, 1234);
	BOOST_CHECK(!test::parse("1", uint4));
	BOOST_CHECK(test::parse_attr("014567", uint4, u));
	BOOST_CHECK_EQUAL(u, 145);

	numeric_parser<unsigned int, mpl::x11::map<
		mpl::x11::pair<with_extractor, standard::digit_type>,
		mpl::x11::pair<
			with_integer,
			detail::fixed_ascii_integer<
				unsigned int, 10, 4
			>
		>,
		mpl::x11::pair<with_filter, detail::length_filter<4>>
	>> uint_exact4;

	char const *first = "0000000";
	char const *last  = first + std::strlen(first);
	BOOST_CHECK(spirit::qi::parse(first, last, uint_exact4, u));
	BOOST_CHECK(first != last);
	BOOST_CHECK_EQUAL(last - first, 3);
	BOOST_CHECK_EQUAL(u, 0);

	first = "0001400";
	last  = first + std::strlen(first);
	BOOST_CHECK(spirit::qi::parse(first, last, uint_exact4, u));
	BOOST_CHECK(first != last);
	BOOST_CHECK_EQUAL(last - first, 3);
	BOOST_CHECK_EQUAL(u, 1);
}

BOOST_AUTO_TEST_CASE(uint_5)
{
	using boost::spirit::_1;
	using boost::phoenix::ref;
	using boost::spirit::standard::space;
	unsigned int n, m;

	BOOST_CHECK(test::parse("123", uint_[ref(n) = _1]));
	BOOST_CHECK_EQUAL(n, 123);
	BOOST_CHECK(test::parse("   456", uint_[ref(n) = _1], space));
	BOOST_CHECK_EQUAL(n, 456);

	BOOST_CHECK(test::parse("123", uint_(123)[ref(n) = _1]));
	BOOST_CHECK_EQUAL(n, 123);
	BOOST_CHECK(!test::parse("123", uint_(321)[ref(n) = _1]));

	BOOST_CHECK(test::parse_attr("789", uint_(789)[ref(n) = _1], m));
	BOOST_CHECK_EQUAL(n, 789);
	BOOST_CHECK_EQUAL(m, 789);
	BOOST_CHECK(!test::parse_attr("789", uint_(987)[ref(n) = _1], m));

	BOOST_CHECK(test::parse("   456", uint_(456)[ref(n) = _1], space));
	BOOST_CHECK_EQUAL(n, 456);
	BOOST_CHECK(!test::parse("   456", uint_(654)[ref(n) = _1], space));

	n = 123;
	m = 321;

	BOOST_CHECK(test::parse("123", uint_(ref(n))));
	BOOST_CHECK(!test::parse("123", uint_(ref(m))));
}

BOOST_AUTO_TEST_CASE(uint_6)
{
	uint8_t u8;
	numeric_parser<uint8_t, uint_policy<uint8_t>> uint8_;

	BOOST_CHECK(test::parse_attr("999", uint8_, u8));
	BOOST_CHECK_EQUAL(u8, 99);
	BOOST_CHECK(test::parse_attr("256", uint8_, u8));
	BOOST_CHECK_EQUAL(u8, 25);
	BOOST_CHECK(test::parse_attr("255", uint8_, u8));
	BOOST_CHECK_EQUAL(u8, 255);

	uint16_t u16;
	numeric_parser<uint16_t, uint_policy<uint16_t>> uint16_;

	BOOST_CHECK(test::parse_attr("99999", uint16_, u16));
	BOOST_CHECK_EQUAL(u16, 9999);
	BOOST_CHECK(test::parse_attr("65536", uint16_, u16));
	BOOST_CHECK_EQUAL(u16, 6553);
	BOOST_CHECK(test::parse_attr("65535", uint16_, u16));
	BOOST_CHECK_EQUAL(u16, 65535);

	uint32_t u32;
	numeric_parser<uint32_t, uint_policy<uint32_t>> uint32_;

	BOOST_CHECK(test::parse_attr("9999999999", uint32_, u32));
	BOOST_CHECK_EQUAL(u32, 999999999);
	BOOST_CHECK(test::parse_attr("4294967296", uint32_, u32));
	BOOST_CHECK_EQUAL(u32, 429496729);
	BOOST_CHECK(test::parse_attr("4294967295", uint32_, u32));
	BOOST_CHECK_EQUAL(u32, 4294967295);
}


BOOST_AUTO_TEST_CASE(uint_7)
{
	using boost::spirit::lit;
	unsigned int i = 123456;

	BOOST_CHECK(test::parse("123456", lit(_r(123456U))));
	BOOST_CHECK(!test::parse("123456", lit(_r(0U))));
	BOOST_CHECK(test::parse("123456", lit(_r(i))));
	BOOST_CHECK(!test::parse("123456", lit(_r(i - 1U))));
}

BOOST_AUTO_TEST_CASE(uint_8)
{
	using boost::spirit::lit;
	unsigned long long ll = 1234567890123456789ULL;

	BOOST_CHECK(test::parse(                                       \
		"1234567890123456789", lit(_r(1234567890123456789ULL)) \
	));
	BOOST_CHECK(!test::parse("1234567890123456789", lit(_r(0ULL))));
	BOOST_CHECK(test::parse("1234567890123456789", lit(_r(ll))));
	BOOST_CHECK(!test::parse(                                      \
		"1234567890123456789", lit(_r(ll - 1ULL))              \
	));
}

BOOST_AUTO_TEST_CASE(uint_9)
{
	unsigned short s = 12345;
	unsigned long l = 1234567890UL;

	BOOST_CHECK(test::parse("12345", lit(_r(s))));
	BOOST_CHECK(!test::parse("12345", lit(_r<unsigned short>(s - 1))));
	BOOST_CHECK(test::parse("1234567890", lit(_r(1234567890UL))));
	BOOST_CHECK(!test::parse("1234567890", lit(_r(98765321UL))));
	BOOST_CHECK(test::parse("1234567890", lit(_r(l))));
	BOOST_CHECK(!test::parse("1234567890", lit(_r(l - 1UL))));
}

BOOST_AUTO_TEST_CASE(uint_10)
{
	unsigned int u;

	BOOST_CHECK(test::parse("123456", uint_(123456)));
	BOOST_CHECK(!test::parse("123456", uint_(654321)));
	BOOST_CHECK(test::parse_attr("123456", uint_(123456), u));
	BOOST_CHECK_EQUAL(u, 123456);
	BOOST_CHECK(!test::parse_attr("123456", uint_(654321), u));

	BOOST_CHECK(test::parse(test::max_unsigned, uint_(UINT_MAX)));
	BOOST_CHECK(test::parse_attr(test::max_unsigned, uint_(UINT_MAX), u));
	BOOST_CHECK_EQUAL(u, UINT_MAX);
}

BOOST_AUTO_TEST_CASE(uint_11)
{
	unsigned int u;

	BOOST_CHECK(test::parse("11111110", bin(0xFE)));
	BOOST_CHECK(!test::parse("11111110", bin(0xEF)));
	BOOST_CHECK(test::parse_attr("11111110", bin(0xFE), u));
	BOOST_CHECK_EQUAL(u, 0xFE);
	BOOST_CHECK(!test::parse_attr("11111110", bin(0xEF), u));

	BOOST_CHECK(test::parse(test::max_binary, bin(UINT_MAX)));
	BOOST_CHECK(test::parse_attr(test::max_binary, bin(UINT_MAX), u));
	BOOST_CHECK_EQUAL(u, UINT_MAX);
}

BOOST_AUTO_TEST_CASE(uint_12)
{
	unsigned int u;

	BOOST_CHECK(test::parse("12545674515", oct(012545674515)));
	BOOST_CHECK(test::parse_attr("12545674515", oct(012545674515), u));
	BOOST_CHECK_EQUAL(u, 012545674515);

	BOOST_CHECK(test::parse(test::max_octal, oct(UINT_MAX)));
	BOOST_CHECK(test::parse_attr(test::max_octal, oct(UINT_MAX), u));
	BOOST_CHECK_EQUAL(u, UINT_MAX);
}

BOOST_AUTO_TEST_CASE(uint_13)
{
	unsigned int u;

	BOOST_CHECK(test::parse("95BC8DF", hex(0x95BC8DF)));
	BOOST_CHECK(!test::parse("95BC8DF", hex(0xFD8CB59)));
	BOOST_CHECK(test::parse_attr("95BC8DF", hex(0x95BC8DF), u));
	BOOST_CHECK_EQUAL(u, 0x95BC8DF);
	BOOST_CHECK(!test::parse_attr("95BC8DF", hex(0xFD8CB59), u));

	BOOST_CHECK(test::parse("abcdef12", hex(0xabcdef12)));
	BOOST_CHECK(!test::parse("abcdef12", hex(0x12fedcba)));
	BOOST_CHECK(test::parse_attr("abcdef12", hex(0xabcdef12), u));
	BOOST_CHECK_EQUAL(u, 0xabcdef12);
	BOOST_CHECK(!test::parse_attr("abcdef12", hex(0x12fedcba), u));

	BOOST_CHECK(test::parse(test::max_hex, hex(UINT_MAX)));
	BOOST_CHECK(test::parse_attr(test::max_hex, hex(UINT_MAX), u));
	BOOST_CHECK_EQUAL(u, UINT_MAX);
}

BOOST_AUTO_TEST_CASE(uint_14)
{
	numeric_parser<
		unsigned long long,
		typename mpl::x11::insert<
			uint_policy<unsigned long long>,
			mpl::x11::pair<
				with_filter, test::ts_filter
			>
		>::type
	> uint_ts;

	unsigned long long u;

	BOOST_CHECK(test::parse_attr("1,234,567,890", uint_ts, u));
	BOOST_CHECK_EQUAL(u, 1234567890ULL);
	BOOST_CHECK(test::parse_attr("12,345,678,900", uint_ts, u));
	BOOST_CHECK_EQUAL(u, 12345678900ULL);
	BOOST_CHECK(test::parse_attr("123,456,789,000", uint_ts, u));
	BOOST_CHECK_EQUAL(u, 123456789000ULL);
	BOOST_CHECK(!test::parse_attr("1000,234,567,890", uint_ts, u));
	BOOST_CHECK(!test::parse_attr("1,234,56,890", uint_ts, u));
	BOOST_CHECK(!test::parse_attr("1,66", uint_ts, u));
}

#if 0
BOOST_AUTO_TEST_CASE(uint_15)
{
	custom_uint u;

	BOOST_CHECK(test::parse_attr("123456", uint_, u));
	uint_parser<custom_uint, 10, 1, 2> uint2;
	BOOST_CHECK(test::parse_attr("12", uint2, u));


	BOOST_CHECK(test::parse_attr("123456", uint_(123456), u));
	uint_parser<custom_uint, 10, 1, 2> uint2;
	BOOST_CHECK(test::parse_attr("12", uint2(12), u));
}
#endif
}}}}
