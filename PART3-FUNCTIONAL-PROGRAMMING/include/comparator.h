#ifndef IEEE_COMPARATOR_H
#define IEEE_COMPARATOR_H

/**
 * Simple comparator function for integers.
 *
 * The comparator function has the following behavior:
 * - return =0 if `a` is equal to `b`
 * - return >0 if `a` is greater than `b`
 * - return <0 if `a` is less than `b`
 * */
int comparator_int(int a, int b);

/**
 * Simple comparator function for characters.
 *
 * The comparator function has the following behavior:
 * - return =0 if `a` is equal to `b`
 * - return >0 if `a` is greater than `b`
 * - return <0 if `a` is less than `b`
 * */
int comparator_char(char a, char b);

#endif //IEEE_COMPARATOR_H
