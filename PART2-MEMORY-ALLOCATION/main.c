#include <stdio.h>
#include <stdlib.h>

#include "fibonacci-gen.h"

void demonstrate_stack_alloc(void);
void demonstrate_heap_alloc(void);
void demonstrate_heap_array_alloc(void);
void demonstrate_heap_ptr_array_alloc(void);

int main(int argc, char *argv[])
{
	// Allocate on Stack
	demonstrate_stack_alloc();

	// Allocate single entity on heap
	demonstrate_heap_alloc();

	// Allocate array of entities on heap
	demonstrate_heap_array_alloc();

	// Allocate array of pointers to entities on the heap
	demonstrate_heap_ptr_array_alloc();

	return 0;
}

/**
 * The purpose of this function is to demonstrate allocating an array on
 * the stack. Once this function returns, the array and its contents are lost.
 *
 * You'll also notice that I assign values to the array in two different ways.
 * The first method is the preferred method for assigning values to an array.
 * However, the second method better describes what is happening under the
 * hood when you use `[]`.
 * */
void demonstrate_stack_alloc(void)
{
	int array[12];

	array[0] = 2;
	*(array + 1) = 3;
}

/**
 * Demonstrate how to allocate memory on the heap. In this case, only a single
 * integer value is stored on the heap.
 *
 * Note that we are checking the pointer returned by malloc() for null. Also
 * note that we must free the memory once done with it.
 * */
void demonstrate_heap_alloc(void)
{
	int *value = (int *)malloc(sizeof(int));
	if(value == NULL) {
		perror("Fatal error: Cannot allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	*value = 12;

	fprintf(stdout, "%d\n", *value);

	free(value);
}

/**
 * Demonstrate how to allocate an array on the heap.
 *
 * Generate the first 15 numbers of the fibonacci sequence and insert into
 * the array.
 * */
void demonstrate_heap_array_alloc(void)
{
	size_t len = 15;
	int *values = (int *)malloc(sizeof(int) * len);
	if(values == NULL) {
		perror("Fatal error: Cannot allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	int ret = gen_fib(values, len);
	if(ret) {
		fprintf(stderr, "Unexpected error occurred.\n");
		exit(EXIT_FAILURE);
	}

	fprintf(stdout, "Fibonacci Sequence:\n");
	for(size_t i = 0; i < len; i++)
		fprintf(stdout, "%d ", values[i]);

	fprintf(stdout, "\n");

	free(values);
}

/**
 * Demonstrate that we can store an array of pointers, where each pointer
 * pointers to a specific chunk of memory.
 *
 * Note that when we allocate an array of pointers, we need to allocate an array,
 * but also each element individually as well. This is a bit more cumbersome,
 * because now we need to free each value in the array before we free the array
 * itself.
 * */
void demonstrate_heap_ptr_array_alloc(void)
{
	size_t len = 15;
	int **values = (int **)malloc(sizeof(int *) * len);
	if(values == NULL) {
		perror("Fatal error: Cannot allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	for(size_t i = 0; i < len; i++) {
		int *value = (int *)malloc(sizeof(int));
		if(value == NULL) {
			perror("Fatal error: Cannot allocate memory.\n");
			exit(EXIT_FAILURE);
		}

		values[i] = value;
	}

	int ret = gen_fib_ptr(values, len);
	if(ret) {
		fprintf(stderr, "Unexpected error occurred.\n");
		exit(EXIT_FAILURE);
	}

	fprintf(stdout, "Fibonacci Sequence:\n");
	for(size_t i = 0; i < len; i++) {
		fprintf(stdout, "%d ", *values[i]);

		free(values[i]);
	}

	fprintf(stdout, "\n");

	free(values);
}
