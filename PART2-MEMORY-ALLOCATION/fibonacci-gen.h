#ifndef IEEE_FIBONACCI_GEN_H
#define IEEE_FIBONACCI_GEN_H

/**
 * Generate the first len numbers in the fibonacci sequence
 * and store in array.
 *
 * Returns 0 on success, and 1 on failure.
 * */
int gen_fib(int array[], size_t len);

/**
 * Generate the first len numbers in the fibonacci sequence
 * and store in array.
 *
 * Returns 0 on success, and 1 on failure.
 * */
int gen_fib_ptr(int *array[], size_t len);

#endif //IEEE_FIBONACCI_GEN_H
