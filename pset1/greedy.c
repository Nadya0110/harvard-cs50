/**
 * greedy.c
 *
 * gets the minimum number of coins needed to repay some amount of change
 */

#include <stdio.h>
#include <cs50.h>
#include <math.h>

float get_positive_float(void);

int main(void) {
  int change = round(get_positive_float() * 100);
  int coins = 0;

  // quarters
  coins += change / 25;
  change %= 25;

  // dimes
  coins += change / 10;
  change %= 10;

  // nickels
  coins += change / 5;
  change %= 5;

  // pennies
  coins += change;

  printf("%i\n", coins);
}

/**
 * gets a positive float from the user
 */
float get_positive_float(void) {
  float f;
  do {
    printf("change: ");
    f = get_float();
  } while (f < 0.0);
  return f;
}
