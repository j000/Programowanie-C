#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define _DOUBLE
/*
double
base: 2
sign bits: 1
significand bits: 53
exponent bits: 11
exponent bias: 2^10-1 = 1023
*/

#define CONCAT2(x, y) x ## y
#define CONCAT(x, y) CONCAT2(x, y)

#ifdef _DOUBLE
#  define TYPE double
#else
#  define TYPE float
#endif
#define UNION CONCAT(u, TYPE)
#ifdef _DOUBLE
#  define UINT unsigned long
#else
#  define UINT unsigned
#endif
#define SHOW CONCAT(show_, TYPE)

typedef union {
	/* double f; */
	TYPE f;
	/* unsigned long u; */
	UINT u;
} UNION;

char *insert(char *into, char *what, unsigned where) {
	char *out = malloc(strlen(into) + strlen(what) + 1);

	strncpy(out, into, where);
	out[where] = '\0';
	strcat(out, what);
	strcat(out, into + where);
	return out;
}

char *binary(UNION a) {
	unsigned size = sizeof(a) * 8;
	char *out = malloc((size + 1) * sizeof(char));
	unsigned i;

	for (i = size; i > 0; --i) {
		out[size - i] = (a.u & (1ul << (i - 1))) ? '1' : '0';
	}
	out[size] = 0;
	return out;
}

char *show_double(UNION a) {
	return insert(insert(binary(a), "-", 1), "-", 11 + 2);
}

char *show_float(UNION a) {
	return insert(insert(binary(a), "-", 1), "-", 8 + 2);
}

int main(int argc, char **argv) {
	UNION a;
	int i;

	/* bail when wrong types are selected */
	if (sizeof(TYPE) != sizeof(UINT)) {
		fprintf(stderr,
			"Types have wrong size!\nfloat: %lu != unsigned: %lu\nFix your code.",
			sizeof(TYPE), sizeof(UINT));
		return EXIT_FAILURE;
	}

	a.f = 1.0;
	a.u = 1;
	a.f = HUGE_VAL;
	printf("%15f: %s\n", a.f, SHOW(a));
	a.f = -(1. / 0.);
	printf("%15f: %s\n", a.f, SHOW(a));
	a.f = -(0. / 0.);
	printf("%15f: %s\n", a.f, SHOW(a));
	a.f = 0. / 0.;
	printf("%15f: %s\n", a.f, SHOW(a));
	for (i = 0; i < 16; ++i) {
		a.f = (double)i / 10;
		printf("%15f: %s\n", a.f, SHOW(a));
	}
	return EXIT_SUCCESS;
}
