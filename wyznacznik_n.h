#ifndef WYZNACZNIK_N_H
#  define WYZNACZNIK_N_H

#  include <stdio.h>
#  include <stdlib.h>
#  include <string.h>		 /* memcpy() */
#  include <alloca.h>
#  include <errno.h>

/* int metoda_wyznacznikow(int, char **); */
int metoda_wyznacznikow(unsigned);
double wyznacznik(unsigned, double *);
unsigned uklad(unsigned int, double[], double[], double[]);

enum {
	BRAK,
	JEDNO,
	WIELE
};

#endif /* WYZNACZNIK_N_H */
