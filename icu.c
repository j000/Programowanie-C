#include <stdio.h>
#include <stdlib.h>

#include <unicode/ustdio.h>
#include <unicode/uchar.h>

/**
 * Reads a UTF-8 file and returns an UChar array containing the string read.
 *
 * @param filename the path to the file to be read
 * @param size pointer to a variable in which to store the UTF-8 string length
 *
 * @return UTF-8 string (dynamically allocated; must be freed after usage)
 */
UChar *read_utf8_file(const char *filename, long *size) {
	UChar *str;

	/* open a UTF-8 file for reading */
	UFILE *f = u_fopen(filename, "r", NULL, "UTF-8");

	/* get the file size */
	long fsize;

	fseek(u_fgetfile(f), 0, SEEK_END);
	fsize = ftell(u_fgetfile(f));
	u_frewind(f);

	/* allocate enough memory to store the whole string plus termination */
	str = (UChar *) malloc(sizeof(UChar) * (fsize + 1));

	/* read the string into the allocated space */
	for ((*size) = 0; !u_feof(f); ++(*size)) {
		str[*size] = u_fgetc(f);
	}

	/* add NULL termination */
	str[*size] = 0;

	/* close the file resource */
	u_fclose(f);

	return str;
}

int main(int argc, char **argv) {
	UFILE *u_stdout;

	/* read the string and its size */
	long size;
	UChar *str = read_utf8_file("utf8_test.txt", &size);

	/* print the string size */
	printf("String size: %ld\n\n", size);

	/* print the UTF-8 string */
	u_stdout = u_finit(stdout, NULL, NULL);
	u_fprintf(u_stdout, "%S\n", str);
	u_fclose(u_stdout);

	/* free the allocated string */
	free(str);

	return 0;
}
