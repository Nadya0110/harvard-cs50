/**
 * vigenere.c
 * 
 * Implements Vigenere's Cipher
 *
 * usage: vigenere keyword
 */

#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("usage: ./vigenere keyword\n");
    return 1;
  }

  string keyword = argv[1];
  int keyword_len = strlen(keyword);

  // convert keyword to uppercase, as well as validate it
  for(int i = 0; i < keyword_len; i++) {
    if (keyword[i] >= 'a' && keyword[i] <= 'z') keyword[i] -= 32;
    else if (keyword[i] < 'A' || keyword[i] > 'Z') {
      printf("keyword can only contain letters\n");
      return 1;
    }
  }

  string plaintext = get_string();

  // iterate over each character
  for (int i = 0, key_shift = 0, n = strlen(plaintext); i < n; i++, key_shift++) {
    char key = keyword[key_shift % keyword_len] - 65;
    char c = plaintext[i];
    if (c >= 'A' && c <= 'Z') c = 65 + ((c - 65 + key) % 26);
    else if (c >= 'a' && c <= 'z')  c = 97 + ((c - 97 + key) % 26);
    else key_shift--;
    printf("%c", c);
  }
  
  printf("\n");
  return 0;
}
