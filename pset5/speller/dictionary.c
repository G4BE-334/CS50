// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// I'm checking the first two letters in a word to separate the words in buckets
// According to our pairing function used in the hash code we will need 727 buckets
const unsigned int N = 727;

// Number of word in dictionary
unsigned int wordCount = 0;

// Hash table
node *table[N];

// State if dictionary is loaded
bool isLoaded = false;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Check should be case-insensitive
    // Create a new word to be able to modify the word
    char newWord[strlen(word)];
    strcpy(newWord, word);
    for (int i = 0; word[i] != '\0'; i++) {
        newWord[i] = tolower(newWord[i]);
    }
    int index = hash(newWord);
    if (table[index] != NULL) {
        for (node* nodePointer = table[index]; nodePointer != NULL; nodePointer = nodePointer->next) {
            if (strcmp(nodePointer->word, newWord) == 0) {
                return true;
            }
        }
    }
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Having problems with 1-char words
    // Solution:
    if (strlen(word) == 1) {
        return 1;
    }
    int hash = 0;
    int a;
    int b;
    for (int i=0; i < 2; i++) {
        if (i == 0)
            a = word[i] - 'a' + 1;
        else
            if (isalpha(word[i]))
                b = word[i] - 'a' + 1;
            else
                i++;
                b = word[i] - 'a' + 1;
    }
    // Pairing function that outputs an uniquely non-negative integer associated with that pair
    hash = ((a^2) + (3*a) + (2*a*b) + b + (b^2))/2;
    // TODO
    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL){
        printf("Could not open file %s", dictionary);
        return false;
    }

    // Clean the past hash table
    for (int i = 0; i < N; i++) {
        table[i] = NULL;
    }
    // Read each word and create a new node for each string
    char str[LENGTH + 1];
    while (fscanf(dic, "%s", str) != EOF) {
        wordCount++;
        node *n = malloc(sizeof(node));
        if (n == NULL) {
            free(n);
        }
        strcpy(n->word, str);

        // Use the hash function here to hash the words and get an index for each string
        int index = hash(str);

        // Insert nodes into hash table, make sure to do it in the right order
        n->next = table[index];
        table[index] = n;
    }
    fclose(dic);
    isLoaded = true;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (!isLoaded) {
        return 0;
    }
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    if (!isLoaded) {
        return false;
    }

    for (int i = 0; i < N; i ++)
    {
        if (table[i] != NULL)
        {
            node *pointer = table[i];
            while (pointer != NULL)
            {
                // Make sure to free the words in the right order to not lose a pointer to a word
                node *newPointer = pointer;
                pointer = pointer->next;
                free(newPointer);
            }
        }
    }
    return true;
}
