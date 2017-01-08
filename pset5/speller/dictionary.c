/**
 * Implements a dictionary's functionality.
 * Using TRIE
 *
 * This version doesn't re-calculate size of dictionary every time size() is called.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "dictionary.h"

// TRIE node
typedef struct node
{
  struct node *children[27];
  bool is_leaf;
} node;

// prototypes
int index_char(char c);
node *create_node();
bool unload_node(node *n);

// word count
unsigned int word_count = 0;

// root node
node *root;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
  node *current_node = root;
  for (int i = 0, len = strlen(word); i < len; i++)
  {
    int index = index_char(word[i]);

    if (current_node -> children[index] == NULL)
      return false;

    current_node = current_node -> children[index];
  }

  return current_node -> is_leaf;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
  word_count = 0;

  // open dictioary
  FILE *fp = fopen(dictionary, "r");
  if (fp == NULL)
    return false;

  // create root TRIE node for dictionary
  root = create_node();
  if (root == NULL)
    return false;

  char buffer[46];

  // iterate over words
  while (fgets(buffer, 47, fp) != NULL)
  {
    int len = strlen(buffer);

    // remove trailing \n
    if (buffer[len - 1] == '\n')
    {
      len--;
      buffer[len] = '\0';
    }

    // set current node to root node
    node *current_node = root;

    // iterate over chars in word
    for (int i = 0; i < len; i++)
    {
      int index = index_char(buffer[i]);

      if (current_node -> children[index] == NULL)
      {
        current_node -> children[index] = create_node();

        // if node is still NULL malloc must have failed
        if (current_node -> children[index] == NULL)
          return false;
      }

      current_node = current_node -> children[index];
    }

    current_node -> is_leaf = true;
    word_count++;
  }

  fclose(fp);

  return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
  return word_count;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
  return unload_node(root);
}

/**
 * returns index based on char
 */
int index_char(char c) {
  if (c == '\'')
    return 26;
  else if (c >= 'A' && c <= 'Z')
    return c - 65;
  else
    return c - 97;
}

/**
 * creates a new node with all NULL children
 */
node *create_node()
{
  node *n = malloc(sizeof(node));
  if (n == NULL)
    return NULL;

  for (int i = 0; i < 27; i++)
    n -> children[i] = NULL;

  n -> is_leaf = false;

  return n;
}

/**
 * frees node n and it's children
 */
bool unload_node(node *n)
{
  for (int i = 0; i < 27; i++)
  {
    if (n -> children[i] != NULL)
      unload_node(n -> children[i]);
  }
  free(n);
  return true;
}
