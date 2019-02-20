#ifndef IEEE_ARRAY_UTILS_H
#define IEEE_ARRAY_UTILS_H

/**
 * Output to stdout each element in the array of pointers, using the to_s
 * implementation provided as an parameter to resolve the pointer to a
 * human readable string.
 *
 * The to_s function must have the following signature:
 * int to_s(void *ptr, char buffer[], size_t buffer_length)
 *
 * where:
 * - ptr is the array element
 * - buffer is the string buffer into which the string should be written
 * - buffer_length is the length of the buffer provided.
 *
 * The to_s function must also indicate to the caller whether the function could
 * successfully resole the pointer to a string by:
 * - returning false on success.
 * - returning true on failure.
 *
 * The output will have a format similar to the example below:
 * Array of Pointers: <string 1> <string 2> ...
 * */
void print_array(void *array[], size_t size, int (*to_s)(void *, char[], size_t));

/**
 * Output to stdout each element in the array of integers. The output will have
 * a format similar to the example below:
 *
 * Array of Integers: 7 3 5 2 8 8 10 6 3 5
 * */
void print_array_int(int array[], size_t size);

/**
 * Output to stdout each element in the array of integers. The output will have
 * a format similar to the example below:
 *
 * Array of Characters: I n s e r t i o n   s o r t   i s   s i m p l e
 * */
void print_array_char(char array[], size_t size);

#endif //IEEE_ARRAY_UTILS_H
