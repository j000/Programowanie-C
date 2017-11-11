#include <stdio.h>
#include <stdlib.h>

#ifdef _DEBUG
#  include <assert.h>
#endif

#include "wyznacznik_n.h"
int kwadratowe(int, char **);

int main(int argc, char **argv) {
#ifdef _DEBUG
	{ /* wyznacznik 3x3 */
		double a[3][3] = {
			{-2, 2, -3},
			{-1, 1, 3},
			{2, 0, -1}
		};
		assert(18 == wyznacznik(3, (double *)a));
	}
	{ /* wyznacznik 3x3 */
		double a[3][3] = {
			{3, 1, 1},
			{2, 2, 3},
			{1, 3, 2}
		};
		assert(-12 == wyznacznik(3, (double *)a));
	}
	{ /* wyznacznik 4x4 */
		double a[4][4] = {
			{0, 1, 2, 7},
			{1, 2, 3, 4},
			{5, 6, 7, 8},
			{-1, 1, -1, 1}
		};
		assert(-64 == wyznacznik(4, (double *)a));
	}
	{ /* układ 2x2 */
		double a[2][2] = {
			{1, 0},
			{0, 1}
		};
		double b[2] = {
			1,
			2
		};
		double x[2] = {0};
		assert(JEDNO == uklad(2, (double *)a, b, x));
		assert(1 == x[0]);
		assert(2 == x[1]);
	}
	{ /* układ 3x3 */
		double a[3][3] = {
			{3, 1, 1},
			{2, 2, 3},
			{1, 3, 2}
		};
		double b[3] = {
			-2,
			8,
			6
		};
		double x[3] = {0};
		assert(JEDNO == uklad(3, (double *)a, b, x));
		assert(-2 == x[0]);
		assert(0 == x[1]);
		assert(4 == x[2]);
	}
	{ /* układ 4x4 */
		double a[4][4] = {
			{1, 1, 1, 1},
			{1, -1, 1, 1},
			{1, -1, -1, 1},
			{2, 1, 1, -1}
		};
		double b[4] = {
			2,
			-2,
			-2,
			5
		};
		double x[4] = {0};
		assert(JEDNO == uklad(4, (double *)a, b, x));
		assert(1 == x[0]);
		assert(2 == x[1]);
		assert(0 == x[2]);
		assert(-1 == x[3]);
	}
#endif
	/* return kwadratowe(argc, argv); */
	return metoda_wyznacznikow(argc, argv);
}

/* vim: tabstop=4 shiftwidth=0 noexpandtab
*/
