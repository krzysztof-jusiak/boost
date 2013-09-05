/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    Based on algorithm from section 10-10 of Hacker's Delight by H. Warren to
    produce multiplicative coefficients for constant division (as used in
    section 10-8 thereof).
==============================================================================*/

#include <limits>
#include <cstdint>
#include <stdio.h>

int main(int argc, char **argv)
{
	unsigned long dr(0);
	if (argc > 1) {
		sscanf(argv[1], "%lu", &dr);
	}

	if (!dr)
		return -1;

	int sh, adj(0);
#if defined(__LP64__)
	unsigned __int128 m;
#else
	unsigned long long m;
#endif

	auto const base_ff(std::numeric_limits<decltype(m)>::max());
	auto const base_7f(base_ff >> 1);
	auto const base_80(base_7f + 1);

	printf("Div %lu, ", dr);

	int p(std::numeric_limits<decltype(m)>::digits - 1);

	decltype(m) d(dr), delta;
	decltype(m) nc(base_ff);
	nc -= ((~d) + 1UL) % d;

	decltype(m) q1(base_80 / nc);
	decltype(m) q2(base_7f / d);

	decltype(m) r1(base_80 - (q1 * nc));
	decltype(m) r2(base_7f - (q2 * d));

	do {
		++p;

		if (r1 >= (nc - r1)) {
			q1 = (q1 << 1) + 1;
			r1 = (r1 << 1) - nc;
		} else {
			q1 <<= 1;
			r1 <<= 1;
		}

		if ((r2 + 1) >= (d - r2)) {
			if (q2 >= base_7f)
				adj = 1;

			q2 = (q2 << 1) + 1;
			r2 = (r2 << 1) + 1 - d;
		} else {
			if (q2 >= base_80)
				adj = 1;

			q2 <<= 1;
			r2 = (r2 << 1) + 1;
		}

		delta = d - 1 - r2;
	} while (
		(p < 2 * std::numeric_limits<decltype(m)>::digits)
		&& (q1 < delta || (q1 == delta && r1 == 0))
	);

	++q2;

	printf("adj %d, ", adj);
	printf(
		"shift %d (%d), ", p,
		p - std::numeric_limits<decltype(m)>::digits
	);
	printf("M %lx_%lx\n", static_cast<unsigned long>(
			q2 >> std::numeric_limits<unsigned long>::digits
		), static_cast<unsigned long>(q2)
	);
	return 0;
}
