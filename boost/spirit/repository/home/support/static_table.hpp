/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_SUPPORT_STATIC_TABLE_JUL_25_2013_1700)
#define SPIRIT_REPOSITORY_SUPPORT_STATIC_TABLE_JUL_25_2013_1700

#include <boost/range/iterator_range.hpp>
#include <boost/iterator/iterator_facade.hpp>

namespace boost { namespace spirit { namespace repository {

template <typename TableData>
struct static_table {
	typedef typename TableData::value_type value_type;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;

	struct const_iterator : boost::iterator_facade<
		const_iterator, const value_type,
		boost::random_access_traversal_tag
	> {
		const_iterator()
		: ptr(nullptr) {}
	
	private:
		friend boost::iterator_core_access;
		friend static_table;

		const_iterator(value_type const *ptr_)
		: ptr(ptr_) {}

		void increment()
		{
			++ptr;
		}

		bool equal(const_iterator const &other) const
		{
			return ptr == other.ptr;
		}

		void advance(difference_type n)
		{
			ptr += n;
		}

		difference_type distance_to(const_iterator const &other) const
		{
			return other.ptr - ptr;
		}

		value_type const &dereference() const
		{
			return *ptr;
		}

		value_type const *ptr;
	};

	typedef boost::iterator_range<const_iterator> range_type;

	constexpr static range_type get(size_type pos)
	{
		return range_type(
			const_iterator(TableData::selector[pos].ptr),
			const_iterator(TableData::selector[pos + 1].ptr)
		);
	}

	template <typename MetaT>
	constexpr static MetaT get_meta(size_type pos)
	{
		return TableData::selector[pos].meta;
	}

	constexpr static size_type size()
	{
		return TableData::size();
	}
};

}}}

#endif
