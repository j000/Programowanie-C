#include <stdio.h>
#include <stdlib.h>

int rownanieKwadratowe(double, double, double, double*, double*);

int main(int argc, char** argv) {
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
	printf("%f * x^2 + %f * x + %f = ", a, b, c);
	if (n == 0) {
		printf("Brak rozwiązań\n");
	} else if (n == 1) {
		printf("%f\n", x1);
	} else {
		printf("%f i %f\n", x1, x2);
	}
	return EXIT_SUCCESS;
}

/* vim: tabstop=4 shiftwidth=0 noexpandtab
*/
