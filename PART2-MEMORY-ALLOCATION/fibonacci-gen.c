#include <stdlib.h>

#include "fibonacci-gen.h"

int gen_fib(int array[], size_t len)
{
	if(array == NULL)
		return 1;

	int n = 0, m = 1, tmp;
	if(len > 0)
		array[0] = n;

	for(size_t i = 1; i < len; i++) {
		array[i] = m;

		tmp = n + m;
		n = m;
		m = tmp;
	}

	return 0;
}

int gen_fib_ptr(int *array[], size_t len)
{
	if(array == NULL)
		return 1;

	int n = 0, m = 1, tmp;
	if(len > 0)
		*array[0] = n;

	for(size_t i = 1; i < len; i++) {
		*array[i] = m;

		tmp = n + m;
		n = m;
		m = tmp;
	}

	return 0;
}