// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <math.h>
#include "dictionary.h"

// value to keep track of dictionary size
int dic_size = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 614656;     // "alphabet hex" to decimal + 1 - accounting for first 4 letters (A through ') (1-27)

// Hash table
node *table[N] = {NULL};


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int numb = hash(word);
    for (node *coo = table[numb]; coo != NULL; coo = coo->next) {
        if (strcasecmp(word, coo->word) == 0) {     //wait.. WORD variable is part of NODE and the variable coming in!!!!!!!uhhh
            return true;
        }
    }
    return false;
}   //WORKS

// Hashes word to a number
unsigned int hash(const char *word)
{
    // hash 'word' into alphabet hex and then convert to decimal
    int ulti_hash = 0;
    int len = strlen(word);
    for (int u = 0; u < len && u < 4; u++)          //ACCOUNT FOR APPOSTRAPHIE.
    {
        int numb;
        if (word[u] != 39) {
        numb = tolower(word[u]) - 96;   // 1-26
        }
        else (numb = 27);       // apostrophie
        ulti_hash += (numb * pow(28, u));   // based on 27^u
    }

    return ulti_hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // open dictionary into "dic"
    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        return false;
    }

    // determining hash value (where to put the node of the word into the hash table)
    char wrd[LENGTH + 1];
    while (fscanf(dic, "%s", wrd) != EOF)                       // go through eveery word in dictionary
    {
        dic_size++;     //keeping track of how many words in dic
        unsigned int hash_num = hash(wrd);                      // returns 1 - 614,656 hash num for putting into hashtable

        struct node *tmp = (struct node *) malloc(sizeof(node));                       // get temporary node
        if (tmp == NULL) return false;

        strcpy(tmp->word, wrd);                                 // defines       temporary
        tmp->next = NULL;                                       //          new             node

        //puts tmp at begining of linked list
        if (1 == 0)
        {
            if (table[hash_num] != NULL) {
                tmp->next = table[hash_num];
            }
            table[hash_num] = tmp;
        }   //WORKS

        //puts tmp at end of linked list
        if (0 == 0)
        {
            if (table[hash_num] == NULL) {
                table[hash_num] = tmp;
            }
            else {
                node *coo = table[hash_num];
                for ( ; coo->next != NULL; coo = coo->next);
                coo->next = tmp;
            }
        }
    }
    //for ( ; table[2]->next != NULL; table[2] = table[2]->next) printf("%s - %s\n", table[2]->word, table[2]->next->word);   //hash table checker
    fclose(dic);
    return true;
}   //WORKS

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dic_size;
}   //WORKS

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{                           //only used malloc to get space for tmp (each new node)
    node *t1;
    node *t2;
    for (int i = 0; i < N; i++) {
        if (table[i] != NULL) {
            t1 = table[i];
            t2 = table[i];
            do {
                t2 = t2->next;
                free(t1);
                t1 = t2;
            } while (t1 != NULL);
        }
    }
    return true;
}   //WORKS
