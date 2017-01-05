/**
 * initials.c
 * 
 * Prints initials of the user's name
 */

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
  string name = get_string();
  if (name == NULL) return 1;

  // if the first char isn't a space, it has to be a letter
  if (name[0] != ' ') printf("%c", toupper(name[0]));

  for (int i = 0, n = strlen(name) - 1; i < n; i++) {
    if (name[i] == ' ' && name[i + 1] != ' ') {
      printf("%c", toupper(name[i + 1]));
      // skip over the next char as we know it isn't a space
      i++;
    }
  }
  printf("\n");
}
