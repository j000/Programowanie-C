#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	/* isatty() */

#ifdef _DEBUG
#  include <assert.h>
#endif

#include "wyznacznik_n.h"
/* int kwadratowe(int, char **); */
void kwadratowe(void);

int menu(void) {
	int n;
	printf("\n--------\n");
	printf("1. Dwumian Newtona\n");
	printf("2. Równanie kwadratowe\n");
	printf("3. Układ 2 równań\n");
	printf("4. Układ n równań\n");
	printf("5. Koniec programu\n");
	printf("\nDokonaj wyboru:\n");
	scanf("%d", &n);
	return n;
}

int noop(void) {
	return 0;
}

/* BLACK MAGIC ;) */
int (*my_printf) (const char *, ...) = printf;

int main(int argc, char **argv) {
	/* bez wypisywania */
	if (!isatty(STDIN_FILENO))
		my_printf = (int (*)(const char *, ...))noop;	

#ifdef _DEBUG
	{
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
	}
#endif
	while (1) {
		switch(menu()) {
			case 1:
				printf("Wybrano dwumian Newtona\n");
				break;
			case 2:
				printf("Wybrano równianie kwadratowe\n");
				kwadratowe();
				break;
			case 3:
				printf("Wybrano układ 2 równań\n");
				metoda_wyznacznikow(2);
				break;
			case 4:
				printf("Wybrano układ n równań\n");
				{
					int n = 0;
					printf("Podaj n: ");
					scanf("%d", &n);
					metoda_wyznacznikow(n);
				}
				break;
			case 5:
				printf("Koniec\n");
				exit(EXIT_SUCCESS);
			default:
				printf("Nie ma takiej opcji\n");
		}
	}
	
	/* nigdy się tu nie znajdziemy */
	return EXIT_FAILURE;
	/* return kwadratowe(argc, argv); */
	/* return metoda_wyznacznikow(argc, argv); */
}

/* vim: tabstop=4 shiftwidth=0 noexpandtab
*/
