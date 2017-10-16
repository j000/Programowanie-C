#include <stdio.h>
#include <stdlib.h>

typedef unsigned long int uli;

/**
 * liczy slinie liczby
 */
uli silnia(int);


uli silnia(int n) {
	uli s=1;
	int i;
	for (i=1; i<=n; ++i) {
		s*=i;
	}
	return s;
}

int main(int argc, char *argv[]) {
	int n;
	printf("Podaj liczbe: ");
	scanf("%d", &n);
	printf("%d! = %lu\n", n, silnia(n));
	return EXIT_SUCCESS;
}

/* vim: tabstop=4 shiftwidth=0 noexpandtab
*/
