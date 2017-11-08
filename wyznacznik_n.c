#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	/* isatty() */
#include <stdarg.h>	/* varargs */
#include <string.h>	/* memcpy() */

/* #include <math.c> */

enum {
	BRAK,
	JEDNO,
	WIELE
};

#if 0
double wyznacznik(unsigned size, double a[][size]) {
	return a[0][0] * a[1][1] - a[1][0] * a[0][1];
}
#else
double wyznacznik(unsigned size, double a[]) {
	double det = 0;
	unsigned i = 0;
	double *tmp;

	if (size == 1)
		return a[0];
	if (size == 2)
		/* a[0][0] * a[1][1] - a[1][0] * a[0][1] */
		/* return a[0 + size * 0] * a[1 + size * 1] - a[1 + size * 0] * a[0 + size * 1]; */
		return a[0] * a[3] - a[1] * a[2];

	/* metoda Laplace’a */
	tmp = (double *)malloc((size - 1) * (size - 1) * sizeof(a[0]));
	if (tmp == NULL)
		exit(EXIT_FAILURE);
	for (i = 0; i < size; ++i) {

		/* det += a[] */
	}
	return det;
}

/* just to skip warning... */

/* #define wyznacznik(x, y) wyznacznik(x, (double*)y) */
#endif

unsigned uklad(unsigned int size, double a[], double b[], double x[]) {
	double w[3] = { 0 };
	double t[2][2];

	/* wyznacznik główny */
	w[0] = wyznacznik(2, a);

	/* wyznacznik 1 */
	memcpy(t, a, sizeof(t));
	t[0][0] = b[0];
	t[1][0] = b[1];
	w[1] = wyznacznik(2, (double *)t);

	/* wyznacznik 2 */
	memcpy(t, a, sizeof(t));
	t[0][1] = b[0];
	t[1][1] = b[1];
	w[2] = wyznacznik(2, (double *)t);

	/* rozwiazania */
	if (w[0] == 0) {
		if (w[1] == 0 && w[2] == 0) {
			/* nieskończenie wiele rozwiązań */
			return WIELE;
		}
		/* brak rozwiązań */
		return BRAK;
	}
	/* jedno roziązanie */
	x[0] = w[1] / w[0];
	x[1] = w[2] / w[0];
	return JEDNO;
}

int noop(void) {
	return 0;
}

int metoda_wyznacznikow(int argc, char *argv[]) {
	double a[2][2] = { 0 };
	double b[2] = { 0 };
	double x[2] = { 0 };
	int i, j;
	int rozwiazania = BRAK;

	/* BLACK MAGIC ;) */
	int (*my_printf) (const char *, ...) = printf;

	if (!isatty(STDIN_FILENO))
		my_printf = (int (*)(const char *, ...))noop;
	/* wczytywanie */
	my_printf("%s\n%30s\n%30s\n",
		"Rowniania:", "a11 * x1 + a12 * x2 = b1", "a21 * x1 + a22 * x2 = b2");
	for (i = 0; i < 2; ++i) {
		for (j = 0; j < 2; ++j) {
			my_printf("Podaj a%d%d: ", i + 1, j + 1);
			scanf("%lf", &a[i][j]);
		}
		my_printf("Podaj b%d: ", i + 1);
		scanf("%lf", &b[i]);
	}
	/* pokaż co liczymy */
	printf("%.3f * x1 + %.3f * x2 = %.3f\n%.3f * x1 + %.3f * x2 = %.3f\n",
		a[0][0], a[0][1], b[0], a[1][0], a[1][1], b[1]);
	/* rozwiąż */
	rozwiazania = uklad(2, (double *)a, b, x);
	/* wypisz wynik */
	if (rozwiazania == WIELE) {
		printf("Nieskończenie wiele rozwiazań.\n");
	} else if (rozwiazania == JEDNO) {
		printf("Jedno rozwiązanie: %.3f i %.3f\n", x[0], x[1]);
	} else {
		printf("Brak rozwiązań.\n");
	}
	return EXIT_SUCCESS;
}

/* vim: tabstop=4 shiftwidth=0 noexpandtab
*/
