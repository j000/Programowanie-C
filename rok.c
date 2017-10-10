#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	int rok;
	printf("Podaj rok urodzenia: ");
	scanf("%d", &rok);
	printf("Masz %d lat\n", 2017-rok);
	return EXIT_SUCCESS;
}
