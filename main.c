#include <stdio.h>
#include <stdlib.h>

int rownanieKwadratowe(double, double, double, double*, double*);

int main(int argc, char** argv) {
	double a,b,c,x1,x2;
	int n;
	/* **** */
	#ifndef __STDC_IEC_559__
	puts("Warning: __STDC_IEC_559__ not defined. IEEE 754 floating point not fully supported.");
	#endif
	/* **** */
	printf("Równanie kwadratowe a*x^2 + b*x + c\n");
	printf("Podaj a: ");
	scanf("%lf", &a);
	printf("Podaj b: ");
	scanf("%lf", &b);
	printf("Podaj c: ");
	scanf("%lf", &c);
	/* **** */
	n = rownanieKwadratowe(a, b, c, &x1, &x2);
	printf("\n%.2f * x^2 + %.2f * x + %.2f = ", a, b, c);
	if (n == 0) {
		printf("Brak rozwiązań\n");
	} else if (n == 1) {
		printf("%.2f\n", x1);
	} else {
		printf("%.2f i %.2f\n", x1, x2);
	}
	return EXIT_SUCCESS;
}

/* vim: tabstop=4 shiftwidth=0 noexpandtab
*/
