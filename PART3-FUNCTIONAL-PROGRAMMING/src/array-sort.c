#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "array-sort.h"
#include "comparator.h"

int insertion_sort(void *array[], size_t size, int (*comparator)(void *, void *))
{
	if(array == NULL)
		return 1;

	for(int i = 1; i < size; i++) {
		void *temp = array[i];
		int j = i - 1;

		while(j >= 0) {
			if((*comparator)(array[j], temp) < 0)
				break;

			array[j+1] = array[j];
			j--;
		}

		array[j+1] = temp;
	}

	return 0;
}

int insertion_sort_int(int array[], size_t size, bool asc)
{
	if(array == NULL)
		return 1;

	for(int i = 1; i < size; i++) {
		int temp = array[i];
		int j = i - 1;

		while(j >= 0) {
			if(asc && comparator_int(array[j], temp) < 0)
				break;

			if(!asc && comparator_int(temp, array[j]) < 0)
				break;

			array[j+1] = array[j];
			j--;
		}

		array[j+1] = temp;
	}

	return 0;
}

int insertion_sort_char(char array[], size_t size, bool asc)
{
	if(array == NULL)
		return 1;

	for(int i = 1; i < size; i++) {
		char temp = array[i];
		int j = i - 1;

		while(j >= 0) {
			if(asc && comparator_char(array[j], temp) < 0)
				break;

			if(!asc && comparator_char(temp, array[j]) < 0)
				break;

			array[j+1] = array[j];
			j--;
		}

		array[j+1] = temp;
	}

	return 0;
}