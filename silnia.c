#include <stdio.h>
#include <stdlib.h>

typedef unsigned long int uli;

/**
 * liczy slinie liczby
 */
/*uli silnia(int);*/
uli silnia(int,char*);


uli silnia(int n, char *error) {
	uli s=1;
	uli t=1;
	int i;
	for (i=2; i<=n; ++i) {
		t*=i;
		if (t>s) {
			s=t;
		} else {
			*error = 1;
			return s;
		}
	}
	return s;
}

int main(int argc, char *argv[]) {
	int n;
	char e=0;
	uli tmp;
	printf("Podaj liczbe: ");
	scanf("%d", &n);
	tmp = silnia(n, &e);
	if (e) {
		printf("Przepełnienie!\nNie mogę policzyć %d!.\nWynik: %lu\n", n, tmp);
		return EXIT_FAILURE;
	}
	printf("%d! = %lu\n", n, tmp);
	return EXIT_SUCCESS;
}

/* vim: tabstop=4 shiftwidth=0 noexpandtab
*/
