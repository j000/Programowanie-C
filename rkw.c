#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int rownanieKwadratowe(double a, double b, double c, double* x1, double* x2) {
	double delta = b * b - 4 * a * c;
	/* brak rozwiązań */
	if (delta < 0) {
		return 0;
	}
	/* jedno rozwiązanie */
	if (delta == 0) {
		*x1 = -b / (2 * a);
		return 1;
	}
	delta = sqrt(delta);
	*x1 = (-b - delta) / a / 2;
	*x2 = (-b + delta) / a / 2;
	return 2;
}

int kwadratowe(int argc, char* argv[]) {
	double a,b,c,x1,x2;
	int n;
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
