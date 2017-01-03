/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // value should be positive
    if (value < 0) return false;
    // search for value using binary search
    for (int max = n, min = 0, mid = n / 2; min != max; mid = (max - min) / 2) {
      if (values[mid] > value) max = mid;
      else if (values[mid] < value) min = mid + 1;
      else return true;
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // array containing the number of times each int upto 65536 is found in values[]
    // all elements are initialized to zero
    int buffer[65536] = {0};
    // fill up buffer with the number of times each number occurs
    for (int i = 0; i < n; i++) {
      buffer[values[i]]++;
    }
    // refill values depending on buffer
    for (int i = 0, c = 0; i < 65536; i++) {
      for (int x = 0; x < buffer[i]; x++, c++) {
        values[c] = i;
      }
    }
    return;
}
