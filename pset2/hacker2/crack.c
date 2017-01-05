/**
 * crack.c
 * 
 * Decrypts ciphertexts encrypted using C's DES-based crypt function 
 *
 * usage: crack ciphertext
 */

#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

bool dict_attack(char *hash, char *salt);
bool brute_force(char *hash, char *salt);
bool brute_alg(char *key, int maxlen, int index, char *hash, char *salt);
bool check_key(char *key, char *salt, char *hash);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("usage: crack ciphertext\n"); return 1;
  }

  // get salt from the first two chars of the hash
  char *salt = malloc(3);
  if (salt == NULL) {
    printf("error allocating memory\n");
    return 1;
  }
  salt[0] = argv[1][0];
  salt[1] = argv[1][1];
  salt[2] = '\0';

  if (dict_attack(argv[1], salt) || brute_force(argv[1], salt)) {
    free(salt);
    return 0;
  }

  printf("crack failed\n");
  free(salt);
  return 0;
}

/**
 * Hashes the words in the dictionary file
 * O(number of lines in file)
 */
bool dict_attack(char *hash, char *salt) {
  FILE *words = fopen("/usr/share/dict/words", "r");
  if (words == NULL) {
    printf("error reading dictionary file\n");
    return 1;
  }

  char *word = malloc(9);
  // while we haven't reached the end of the file
  while (fgets(word, 9, words) != NULL) {
    // strips the new line character from the word
    int last_char = strlen(word) - 1;
    if (word[last_char] == '\n')
      word[last_char] = '\0';

    if (check_key(word, salt, hash)) {
      free(word);
      fclose(words);
      return true;
    }
  }
  free(word);
  fclose(words);
  return false;
}

/**
 * Brute forces to hash every combination of printable ASCII chars (95 total) with a max length of 8 chars
 * O(95^8 + 95^7 + 97^6 ... 95^1 = 276,437,316,705,637,200) lol
 */
bool brute_force(char *hash, char *salt) {
  // max num of chars in key is 8 + 1 null terminator = 9 bytes
  char *key = malloc(9);
  if (key == NULL) {
    printf("error allocating memory\n");
    return false;
  }

  // iterate over all possible combinations of a key of length 1 through 8
  for (int len = 1; len <= 8; len++) {
    // null terminate the string according to the current length
    key[len] = '\0';
    if (brute_alg(key, len, 0, hash, salt)) {
      free(key);
      return true;
    }
  }
  free(key);
  return false;
}

/**
 * Actual brute force algorithm
 * Very inefficient because of recursion, but oh well
 */
bool brute_alg(char *key, int maxlen, int index, char *hash, char *salt) {
  for (char c = ' '; c <= '~'; c++) {
    key[index] = c;
    if (index == maxlen - 1) {
      if (check_key(key, salt, hash))
        return true;
    } else if (brute_alg(key, maxlen, index + 1, hash, salt)) {
      return true;
    }
  }
  return false;
}

/**
 * Checks if given key hashes to the same hash
 */
bool check_key(char *key, char *salt, char *hash) {
  if (strcmp(crypt(key, salt), hash) == 0) {
      printf("%s\n", key);
      return true;
  }
  return false;
}
