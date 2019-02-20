#ifndef IEEE_ARRAY_SORT_H
#define IEEE_ARRAY_SORT_H

/**
 * Sort an array of elements of unknown type.
 *
 * The comparator function must have the following signature:
 * int comparator(void *a, void *b)
 *
 * The comparator function must also have the following behavior:
 * - return =0 if `a` is equal to `b`
 * - return >0 if `a` is greater than `b`
 * - return <0 if `a` is less than `b`
 * */
int insertion_sort(void *array[], size_t size, int (*comparator)(void *, void *));

/**
 * Sort an array of integers in ascending or descending order.
 * */
int insertion_sort_int(int array[], size_t size, bool asc);

/**
 * Sort an array of characters in ascending or decreasing order.
 * */
int insertion_sort_char(char array[], size_t size, bool asc);

#endif //IEEE_ARRAY_SORT_H
