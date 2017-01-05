/**
 * mario.c
 * 
 * Prints a pyramid, n tall
 */

#include <cs50.h>
#include <stdio.h>

int get_valid_int(void);

int main(void) {
  int height = get_valid_int();
  for (int x = 1; x <= height; x++) {
    for (int y = 0; y < height - x; y++) printf(" ");
    for (int y = 0; y <= x; y++) printf("#");
    printf("\n");
  }
}

/**
 * Gets a valid height
 * @return  height
 */
int get_valid_int(void) {
  int n;
  do {
    printf("height: ");
    n = get_int();
  } while (n < 0 || n > 23);
  return n;
}
