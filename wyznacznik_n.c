#include <stdio.h>
#include <stdlib.h>
#include <string.h>			 /* memcpy() */
#include <alloca.h>
#include <errno.h>

#include "wyznacznik_n.h"
int (*my_printf) (const char *, ...);

void *my_malloc(size_t sz) {
	void *tmp = malloc(sz);

	if (tmp != NULL)
		return tmp;
	fprintf(stderr, "Malloc failed (%ld bytes): %s. Aborting.\n", sz,
		strerror(errno));
	exit(EXIT_FAILURE);
}

void *my_calloc(size_t n, size_t sz) {
	void *tmp = calloc(n, sz);

	if (tmp != NULL)
		return tmp;
	fprintf(stderr, "Calloc failed (%ld x %ld bytes): %s. Aborting.\n", n, sz,
		strerror(errno));
	exit(EXIT_FAILURE);
}

double wyznacznik(unsigned size, double a[]) {
	double det = 0;
	unsigned i = 0;
	double *tmp = NULL;

	if (size == 1)
		return a[0];
	if (size == 2)
		/* a[0][0] * a[1][1] - a[1][0] * a[0][1] */
		return a[0] * a[3] - a[1] * a[2];

	/* metoda Laplace’a */
	tmp = alloca(sizeof(*a) * (size - 1) * (size - 1));
	/* kopiuj tablicę a do tmp
	 * z pominięciem
	 * pierszego wiersza
	 * i pierszej kolumny */
	for (i = 1; i < size; ++i) {
		memcpy(&tmp[(size - 1) * (i - 1)], &a[size * i + 1],
			sizeof(*a) * (size - 1));
	}
	for (i = 0; i < size; ++i) {
		/* kopiuj wiersz a[i-1] do tmp[i-1]
		 * (zamiast kopiować całą tablicę)
		 * i pomiń pierwszą kolumnę */
		if (i > 0)
			memcpy(&tmp[(size - 1) * (i - 1)], &a[size * (i - 1) + 1],
				sizeof(*a) * (size - 1));
		/* licz wyznacznik */
		det += ((i % 2) ? -1 : 1) * a[i * size] * wyznacznik(size - 1, tmp);
	}
	return det;
}

unsigned uklad(unsigned int size, double a[], double b[], double x[]) {
	unsigned i, j;
	double *w;
	double *t;

	w = alloca(sizeof(*w) * (size + 1));
	t = alloca(sizeof(*t) * size * size);

	/* wyznacznik główny */
	w[0] = wyznacznik(size, a);

	/* kolejne wyznaczniki */
	for (i = 0; i < size; ++i) {
		/* kopiuj tablicę a[] do t[] */
		memcpy(t, a, sizeof(*t) * size * size);
		/* wczytaj b[] na odpowiednią kolumnę t[] */
		for (j = 0; j < size; ++j) {
			t[i + size * j] = b[j];
		}
		/* wylicz wyznacznik */
		w[i + 1] = wyznacznik(size, t);
	}

	/* rozwiazania */
	if (w[0] == 0) {
		for (i = 1; i <= size; ++i) {
			if (w[i] != 0)	 /* któryś wyznacznik jest różny od zera */
				return BRAK; /* brak rozwiązań */
		}
		/* wszystkie wyznaczniki są równe zero
		 * nieskończenie wiele rozwiązań */
		return WIELE;
	}
	/* jedno roziązanie */
	for (i = 0; i < size; ++i) {
		x[i] = w[i + 1] / w[0];
	}
	return JEDNO;
}

/* int metoda_wyznacznikow(int argc, char *argv[]) { */
	/* unsigned size = 2; */
int metoda_wyznacznikow(unsigned size) {
	double *a;
	double *b;
	double *x;
	unsigned i, j;
	int rozwiazania = BRAK;

	/* rozmiar */
	/*
	if (argc > 1) {
		unsigned tmp = strtol(argv[1], (char **)NULL, 10);
		if (tmp > 0)
			size = tmp;
	}
	*/

	/* pamięć */
	a = alloca(sizeof(*a) * size * size);
	b = alloca(sizeof(*b) * size);
	x = alloca(sizeof(*x) * size);

	/* wczytywanie */
	my_printf("Rownania:\n");
	for (i = 1; i <= size; ++i) {
		my_printf("a%d1 * x1", i);
		for (j = 2; j <= size; ++j) {
			my_printf(" + a%d%d * x%d", i, j, j);
		}
		my_printf(" = b%d\n", i);
	}
	for (i = 0; i < size; ++i) {
		for (j = 0; j < size; ++j) {
			my_printf("Podaj a%d%d: ", i + 1, j + 1);
			scanf("%lf", &a[i * size + j]);
		}
		my_printf("Podaj b%d: ", i + 1);
		scanf("%lf", &b[i]);
	}
	/* pokaż co liczymy */
	for (i = 0; i < size; ++i) {
		printf("%6.2f * x1", a[i * size + 0]);
		for (j = 1; j < size; ++j) {
			printf(" + %6.2f * x%d", a[i * size + j], j + 1);
		}
		printf(" = %6.2f\n", b[i]);
	}
	/* rozwiąż */
	rozwiazania = uklad(size, a, b, x);
	/* wypisz wynik */
	if (rozwiazania == WIELE) {
		printf("Nieskończenie wiele rozwiazań.\n");
	} else if (rozwiazania == JEDNO) {
		printf("Jedno rozwiązanie:\n");
		for (i = 0; i < size; ++i) {
			printf("x%d = %6.2f\n", i + 1, x[i]);
		}
	} else {
		printf("Brak rozwiązań.\n");
	}
	return EXIT_SUCCESS;
}

/* vim: tabstop=4 shiftwidth=0 noexpandtab
*/
