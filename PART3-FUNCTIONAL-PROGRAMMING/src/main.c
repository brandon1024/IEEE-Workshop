#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "array-sort.h"
#include "array-utils.h"
#include "version.h"

struct data_t {
	unsigned long id;
	unsigned char value;
};

void demonstrate_sort_int(void);
void demonstrate_sort_char(void);
void demonstrate_sort_ptr(void);
int custom_comparator(void *a, void *b);
int data_to_s(void *entity, char buffer[], size_t buff_len);
void show_version(void);

/**
 * Run each insertion sort demonstration individually.
 *
 * The first and second parts are used to demonstrate that the sort is functioning
 * correctly, while the third part is used to demonstrate the strategy pattern.
 * */
int main(int argc, char *argv[])
{
	show_version();

	printf("\nPart1:\n");
	demonstrate_sort_int();

	printf("\nPart2:\n");
	demonstrate_sort_char();

	printf("\nPart3:\n");
	demonstrate_sort_ptr();

	return 0;
}

/**
 * Demonstrate sorting an array of integers in descending order.
 *
 * Prints the contents of the array to stdout before and after being sorted.
 * */
void demonstrate_sort_int(void)
{
	const size_t len = 10;
	int array[len] = {7, 3, 5, 2, 8, 8, 10, 6, 3, 5};

	print_array_int(array, len);

	insertion_sort_int(array, len, false);

	print_array_int(array, len);
}

/**
 * Demonstrate sorting an array of characters in ascending order.
 *
 * Prints the contents of the array to stdout before and after being sorted.
 * */
void demonstrate_sort_char(void)
{
	const size_t len = 44;
	char array[len] = "Insertion sort is a simple sorting algorithm";

	print_array_char(array, len);

	insertion_sort_char(array, len, true);

	print_array_char(array, len);
}

/**
 * Demonstrate sorting an array of pointers using a custom comparator strategy.
 *
 * Prints the contents of the array to stdout before and after being sorted.
 * */
void demonstrate_sort_ptr(void)
{
	const size_t len = 5;
	struct data_t **data = (struct data_t **)malloc(sizeof(struct data_t *) * len);
	if(data == NULL) {
		perror("Fatal error: Cannot allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	size_t i;
	unsigned long id = 1;
	unsigned char value = 'a';
	for(i = 0; i < len; i++) {
		data[i] = (struct data_t *)malloc(sizeof(struct data_t *));
		if(data[i] == NULL) {
			perror("Fatal error: Cannot allocate memory.\n");
			exit(EXIT_FAILURE);
		}

		id += id * 4 % (13 - i);
		data[i]->id = id;
		data[i]->value = value++;
	}

	print_array((void **)data, len, &data_to_s);

	insertion_sort((void **)data, len, &custom_comparator);

	print_array((void **)data, len, &data_to_s);

	for(i = 0; i < len; i++)
		free(data[i]);
	free(data);
}

/**
 * Custom implementation of a comparator for an array of data_t structures.
 *
 * This function is passed as an argument to insertion_sort.
 * */
int custom_comparator(void *a, void *b)
{
	struct data_t *x = a;
	struct data_t *y = b;

	if(x == NULL)
		return 1;

	if(y == NULL)
		return -1;

	if(x->id > y->id)
		return -1;

	if(x->id == y->id)
		return 0;

	return 1;
}

/**
 * Custom to_s implementation, used to resolve a pointer to a data_t structure
 * to a string.
 *
 * This function is passed as an argument to print_array.
 * */
int data_to_s(void *entity, char buffer[], size_t buff_len)
{
	struct data_t *data = entity;
	int ret = snprintf(buffer, buff_len, "(%lu, %c)", data->id, data->value);

	return ret < 0 || ret >= buff_len;
}

/**
 * Print to stdout the current version number of this application.
 * */
void show_version(void)
{
	fprintf(stdout, "IEEEP3 version %u.%u\n", IEEEP3_VERSION_MAJOR, IEEEP3_VERSION_MINOR);
}