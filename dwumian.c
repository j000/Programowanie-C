#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef unsigned long int uli;

/**
 * liczy slinie liczby
 */
uli silnia(unsigned);
/**
  * liczy symbol newtona
  */
uli symbol_newtona(unsigned,unsigned);
/**
  * liczy dwumian Newtona
  */
double dwumian(double, double, unsigned);

uli silnia(unsigned n) {
	uli s=1;
	unsigned i;
	for (i=1; i<=n; ++i) {
		s*=i;
	}
	return s;
}

uli symbol_newtona(unsigned n, unsigned k) {
	return silnia(n)/(silnia(k)*silnia(n-k));
}

double dwumian(double a, double b, unsigned n) {
	unsigned i;
	double suma=0;
	for (i=0; i<=n; ++i) {
		suma += symbol_newtona(n, i) * pow(a, n-i) * pow(b, i);
	}
	return suma;
}

int main(int argc, char *argv[]) {
	unsigned n;
	double a,b;
	printf("Podaj n: ");
	scanf("%u", &n);
	printf("Podaj a: ");
	scanf("%lf", &a);
	printf("Podaj b: ");
	scanf("%lf", &b);
	printf("( %f + %f ) ^ %u = %f\n", a, b, n, dwumian(a, b, n));
	return EXIT_SUCCESS;
}

/* vim: tabstop=4 shiftwidth=0 noexpandtab
*/
