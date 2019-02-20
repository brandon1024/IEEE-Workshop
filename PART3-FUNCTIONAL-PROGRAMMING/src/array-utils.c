#include <stdio.h>
#include <stdlib.h>

#include "array-utils.h"

#define BUFF_LEN 64

void print_array(void *array[], size_t size, int (*to_s)(void *, char[], size_t))
{
	fprintf(stdout, "Array of Pointers:");

	char buffer[BUFF_LEN];
	for(size_t i = 0; i < size; i++) {
		int ret = (*to_s)(array[i], buffer, BUFF_LEN);
		if(ret) {
			fprintf(stderr, "Fatal error: Exceeded buffer size.\n");
			exit(EXIT_FAILURE);
		}

		fprintf(stdout, " %s", buffer);
	}

	fprintf(stdout, "\n");
}

void print_array_int(int array[], size_t size)
{
	fprintf(stdout, "Array of Integers:");

	for(size_t i = 0; i < size; i++)
		fprintf(stdout, " %d", array[i]);

	fprintf(stdout, "\n");
}

void print_array_char(char array[], size_t size)
{
	fprintf(stdout, "Array of Characters:");

	for(size_t i = 0; i < size; i++)
		fprintf(stdout, " %c", array[i]);

	fprintf(stdout, "\n");
}