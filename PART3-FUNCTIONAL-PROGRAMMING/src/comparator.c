#include <stdlib.h>

#include "comparator.h"

int comparator_int(int a, int b)
{
	if(a > b)
		return 1;

	if(a == b)
		return 0;

	return -1;
}

int comparator_char(char a, char b)
{
	return comparator_int(a, b);
}