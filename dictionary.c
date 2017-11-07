```
/**
 * Implements a dictionary's functionality.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// define a trie structure
typedef struct trie
{
    bool word;
    struct trie* children[27];
} trie;

// declare an uninitialised trie called root, which is the starting point of the entire trie structure
trie* root;

// declare an unsigned integer to be used later to count the number of words in book
unsigned int word_in_book;

// free the momery of the trie structure recursively
void freenode (trie* node)
{
    for (int i = 0; i < 27; i++)
    {
        if (node->children[i])
        {
            freenode(node->children[i]);
        }
    }
    
    free(node);
}


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // declare a trie called node to duplicate the root
    trie* node = root;
    
    // iterate through the length of the word that requires the checking
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // convert the character to lowercase character
        char c = tolower(word[i]);
        
        // if the character is ', then set its value to a + 26 which is 123
        if (c == '\'')
        {
            c = 123;
        }
        
        // set the sorted pointer to the children of this node
        trie* current = node->children[c - 97];
        
        // if it does not exist, then create one and go to that children. Otherwise, go to the children directly.
        if (current == NULL)
        {
            return false;
        }
        else
        {
            node = current;
        }
    }
    
    return node->word;
}


/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // opens dictionary;
    FILE *d = fopen(dictionary, "r");
    if (d == NULL)
    {
        fprintf(stderr, "Could not open %s\n", dictionary);
        return false;
    }
    
    // assign malloc a chunck of memory with size equivalent to a trie
    root = calloc(1, sizeof(*root));
    
    // declare a trie called node to duplicate root
    trie* node = root;
    
    // iterate through the character in the dictionary file
    for (char c = fgetc(d); c != EOF; c = fgetc(d))
    {
        // if the end of a word is reached and the current node is not the root, then increase the count of word in the book by 1
        // and set the word to true and set the current node to root
        if (c == '\n')
        {
            if (node != root)
            {
                word_in_book++;
                
                node->word = true;
                
                node = root;
            }
        }
        // if the character is not the end of a word
        else
        {
            // if the character is ', then set its value to a + 26, which is 123
            if (c == '\'')
            {
                c = 123;
            }
            
            // set the sorted pointer to the children of this node
            trie* current = node->children[c - 97];
            
            // if it does not exist, then create one and go to that children. Otherwise, go to the children directly.
            if (current == NULL)
            {
                node->children[c - 97] = calloc(1, sizeof (*root));
                
                node = node->children[c - 97];
            }
            else
            {
                node = node->children[c - 97];
            }
        }
        
    }
    
    // close the file and exit the programme with a successful code
    fclose(d);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return word_in_book;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    freenode(root);
    return true;
}
```
