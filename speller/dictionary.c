/**
 * Implements a dictionary's functionality.
 */

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

const int VALIDCHARS = 27;

typedef struct node {
    bool termChar;
    struct node *letter[VALIDCHARS];
} charNode;

void purgeNode(charNode *tNode);

charNode *head;
int dictSize;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
    charNode *curr = head;
    int len = strlen(word);

    for (int ctr=0; ctr<len; ctr++){
        
        int arrIndex = (isalpha(word[ctr])) ? word[ctr] % 32 : 0;
            
        if (curr->letter[arrIndex] == NULL){
            return false;
        }
        else {
            curr = curr->letter[arrIndex];
        }
        
    }
    return curr->termChar;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // TODO
    head = malloc(sizeof(charNode));
    if (head == NULL){
        return false;
    }
    charNode *curr = head;

    FILE *dictptr = fopen(dictionary, "r");
    if (dictptr == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    
    int arrIndex=0;
    // fscanf implementation
    char buffer[LENGTH+1];
    while (fscanf(dictptr,"%s",buffer) != EOF){
        int len = strlen(buffer);
        for(int ctr=0; ctr<len; ctr++){
            arrIndex = (isalpha(buffer[ctr])) ? buffer[ctr]%32 : 0;
            if (curr->letter[arrIndex]==NULL)
                curr->letter[arrIndex]=malloc(sizeof(charNode));
            curr = curr->letter[arrIndex];
        }
        curr->termChar = true;
        curr = head;
        dictSize++;
    }
    // fgetc implementation
    /*for (int c=fgetc(dictptr); c!=EOF; c=fgetc(dictptr)){
        if (c=='\n') {
            curr->termChar = true;
            curr = head;
            dictSize++;
            continue;
        }
        arrIndex = (isalpha(c)) ? c%32 : 0;
        if (curr->letter[arrIndex]==NULL)
            curr->letter[arrIndex]=malloc(sizeof(charNode));
        curr = curr->letter[arrIndex];
    }*/
    
    fclose(dictptr);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return dictSize;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    purgeNode(head);
    return true;
}

void purgeNode(charNode *tNode){
    for (int ctr=0; ctr<VALIDCHARS; ctr++){
        if (tNode->letter[ctr]!=NULL)
            purgeNode(tNode->letter[ctr]);
    }
    free(tNode);
}
