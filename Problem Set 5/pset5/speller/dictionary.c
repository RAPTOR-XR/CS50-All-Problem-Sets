// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = (LENGTH + 1) * 'z';
int tw = 0;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int indx = hash(word);
    node *c = table[indx];
    while (c != NULL)
    {
        if (strcasecmp(c->word, word) == 0)
        {
            return true;
        }
        c = c->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    int sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += toupper(word[i]);
    }
    return (sum % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(f, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, word);
        n->next = NULL;
        
        int indx = hash(word);
        if (table[indx] == NULL)
        {
            table[indx] = n;
        }
        else
        {
            n->next = table[indx];
            table[indx] = n;
        }
        tw++;
    }
    fclose(f);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return tw;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *tmp = head;
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
