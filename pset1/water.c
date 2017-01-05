/**
 * water.c
 * 
 * Reality check: gives the amount of water you take to shower -- in bottles
 */

#include <cs50.h>
#include <stdio.h>

int get_postitive_int(void);

int main(void) {
  int minutes = get_postitive_int();
  printf("bottles: %i\n", 12 * minutes);
}

/**
 * Gets a positive integer from the user
 * @return  a positive integer
 */
int get_postitive_int(void) {
  int x;
  do {
    printf("minutes: ");
    x = get_int();
  } while(x < 1);
  return x;
}
