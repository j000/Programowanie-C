#include <stdio.h>
#include <stdlib.h>
/* #include <math.c> */

enum {
	BRAK,
	JEDNO,
	WIELE
};

double wyznacznik(double a[][2]) {
	return a[0][0] * a[1][1] - a[1][0] * a[0][1];
}

unsigned uklad2(double a[][2], double b[], double x[]) {
	double w[3] = {0};
	double t[2][2];
	/* wyznacznik główny */
	w[0] = wyznacznik(a);

	/* wyznacznik 1 */
	t[0][0] = b[0];
	t[0][1] = a[0][1];
	t[1][0] = b[1];
	t[1][1] = a[1][1];
	w[1] = wyznacznik(t);

	/* wyznacznik 2 */
	t[0][0] = a[0][0];
	t[0][1] = b[0];
	t[1][0] = a[1][0];
	t[1][1] = b[1];
	w[2] = wyznacznik(t);

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
	x[0] = w[1]/w[0];
	x[1] = w[2]/w[0];
	return JEDNO;
}

int metoda_wyznacznikow(int argc, char* argv[]) {
	double a[2][2] = {0};
	double b[2] = {0};
	double x[2] = {0};
	int i, j;
	int rozwiazania = BRAK;
	/* **** */
	printf("%s\n%30s\n%30s\n", "Rowniania:", " a11 * x1 + a12 * x2 = b1", "a21 * x1 + a22 * x2 = b2");
	for (i=0; i<2; ++i) {
		for (j=0; j<2; ++j) {
			printf("Podaj a%d%d: ", i+1, j+1);
			scanf("%lf", &a[i][j]);
		}
		printf("Podaj b%d: ", i+1);
		scanf("%lf", &b[i]);
	}
	printf("\n");
	/* **** */
	printf("%.3f * x1 + %.3f * x2 = %.3f\n%.3f * x1 + %.3f * x2 = %.3f\n",
			a[0][0], a[1][0], b[0],
			a[1][0], a[1][1], b[1]
		  );
	rozwiazania = uklad2(a, b, x);
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
