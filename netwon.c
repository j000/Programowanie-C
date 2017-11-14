#include <stdio.h>
#include <stdlib.h>

typedef unsigned long int uli;

/**
 * liczy slinie liczby
 */
uli silnia(unsigned);

/**
 * liczy symbol newtona
 */
uli symbol_newtona(unsigned, unsigned);

uli silnia(unsigned n) {
	uli s = 1;
	unsigned i;

	for (i = 1; i <= n; ++i) {
		s *= i;
	}
	return s;
}

uli symbol_newtona(unsigned n, unsigned k) {
	return silnia(n) / (silnia(k) * silnia(n - k));
}

int main(int argc, char *argv[]) {
	unsigned n, k;

	printf("Podaj n: ");
	scanf("%u", &n);
	/*printf("%u! = %lu\n", n, silnia(n)); */
	printf("Podaj k: ");
	scanf("%u", &k);
	printf("%u po %u = %lu\n", n, k, symbol_newtona(n, k));
	return EXIT_SUCCESS;
}

/* vim: tabstop=4 shiftwidth=0 noexpandtab
*/
