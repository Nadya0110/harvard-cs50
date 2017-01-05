/**
 * credit.c
 * 
 * Validates credit card number
 */

#include <cs50.h>
#include <stdio.h>

bool checksum(long long num);
int get_length(long long num);
int get_first_digits(long long num);

int main(void) {
  // let card status be "INVALID" by default
  string status = "INVALID";

  printf("number: ");
  long long num = get_long_long();

  // confirm checksum
  if (checksum(num)) {
    // length of the credit card num
    int len = get_length(num);
    // first two digits of the credit card num
    int first_digits = get_first_digits(num);

    if (len == 15 && (first_digits == 34 || first_digits == 37)) status = "AMEX";
    else if (len == 16 && first_digits >= 51 && first_digits <= 55) status = "MASTER CARD";
    else if ((len == 13 || len == 16) && first_digits / 10 == 4) status = "VISA";
    else status = "INVALID";
  }

  printf("%s\n", status);
}

/**
 * checks the credit card number by the checksum algorithm
 * @param  num credit card num
 * @return     validity
 */
bool checksum(long long num) {
  // stores digit index
  int len = 0;
  int sum = 0;

  // iterates over the digits in the credit card num
  while (num > 0) {
    len++;

    // if the digit is even, multiply it by two
    if (len % 2 == 0) {
      int x = (num % 10) * 2;
      // iterates over the digits in integer x
      while (x > 0) {
        sum += x % 10;
        x /= 10;
      }
    }
    
    else sum += num % 10;
    num /= 10;
  }

  return sum % 10 == 0;
}

/**
 * gets the length of the credit card num
 * @param  num credit card num
 * @return     length
 */
int get_length(long long num) {
  int len = 0;

  // iterates over the digits of the num
  while (num > 0) {
    len++;
    // truncate the num by a place
    num /= 10;
  }

  return len;
}

/**
 * gets the first two digits of the credit card num
 * @param  num credit card num
 * @return     first two digits
 */
int get_first_digits(long long num) {
  // while the num has three digits or more
  while (num >= 100)
    // truncate the num by a place
    num /= 10;

  return (int) num;
}
