#include <stdio.h>
#include <stdlib.h>

#ifdef _DEBUG
#  include <assert.h>
#endif

int kwadratowe(int, char **);
int metoda_wyznacznikow(int, char **);

#ifdef _DEBUG
double wyznacznik(unsigned, double *);
#endif

int main(int argc, char **argv) {
#ifdef _DEBUG
	{
		double a[4][4] = {
			{0, 1, 2, 7},
			{1, 2, 3, 4},
			{5, 6, 7, 8},
			{-1, 1, -1, 1}
		};
		assert(-64 == wyznacznik(4, (double *)a));
	}
	{
		double a[3][3] = {
			{-2, 2, -3},
			{-1, 1, 3},
			{2, 0, -1}
		};
		assert(18 == wyznacznik(3, (double *)a));
	}
#endif
	/* return kwadratowe(argc, argv); */
	return metoda_wyznacznikow(argc, argv);
}

/* vim: tabstop=4 shiftwidth=0 noexpandtab
*/
