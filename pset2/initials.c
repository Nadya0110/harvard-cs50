/**
 * initials.c
 * 
 * prints initials of the user's name
 */

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
  string name = get_string();
  if (name == NULL) return 1;

  // the first char has to be the first initial
  printf("%c", toupper(name[0]));

  // start from index 1 as 0 has to be a char
  for (int i = 1, n = strlen(name) - 1; i < n; i++) {
    if (name[i] == ' ') {
      printf("%c", toupper(name[i + 1]));
      // skip over the next char as we know it isn't a space
      i++;
    }
  }
  printf("\n");
}
