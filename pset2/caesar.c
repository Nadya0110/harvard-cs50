#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("usage: ./caesar key\n");
    return 1;
  }

  int key = atoi(argv[1]);
  if (key < 0) {
    printf("key has to be positive\n");
    return 1;
  }

  string plaintext = get_string();

  // iterate over each character
  for (int i = 0, n = strlen(plaintext); i < n; i++) {
    char c = plaintext[i];
    if (c >= 'A' && c <= 'Z') c = 65 + ((c - 65 + key) % 26);
    else if (c >= 'a' && c <= 'z')  c = 97 + ((c - 97 + key) % 26);;
    printf("%c", c);
  }
  printf("\n");
  return 0;
}
