#include <math.h>

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
	*x1 = -b - delta / a / 2;
	*x2 = -b + delta / a / 2;
	return 2;
}

/* vim: tabstop=4 shiftwidth=0 noexpandtab
*/
