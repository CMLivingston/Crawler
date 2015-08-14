/* ========================================================================== */
/* File: hashtable.c
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: Crawler
 *
 * Author: Chris Livingston
 * Date: 
 *
 */
/* ========================================================================== */

// ---------------- Open Issues

// ---------------- System includes e.g., <stdio.h>
#include <string.h>                         // strlen, strcmp
#include <stdio.h>                         // I/O


// ---------------- Local includes  e.g., "file.h"
#include "hashtable.h"                        // hashtable functionality

// ---------------- Constant definitions

// ---------------- Macro definitions

// ---------------- Structures/Types

// ---------------- Private variables

// ---------------- Private prototypes
int strcmp(const char *str1, const char *str2);
int strncmp(const char *str1, const char *str2, size_t n);
size_t strlen(const char *str);
char *strcpy(char *dest, const char *src);
void *malloc(size_t size);
char *strdup (const char *s);
void free(void *ptr);
// ---------------------------------------


unsigned long JenkinsHash(const char *str, unsigned long mod)
{
    size_t len = strlen(str);
    unsigned long hash, i;

    for(hash = i = 0; i < len; ++i)
    {
        hash += str[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash % mod;
}

HashTable *initTable(){
  HashTable* d = (HashTable*)malloc(sizeof(HashTable));
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->table[i] = NULL;
  }
  return d;
}


// Returns 1 or 0 for false or true that the table contains the node, repectively 
int HashTableLookup(HashTable *table, char *url){

    long int lookupHashIndex = JenkinsHash(url, MAX_HASH_SLOT);
    int uniqueBool = 2; // 0 for true, 1 for false, 2 for init
    int sameCount = 0; // to track repeats
   
    HashTableNode* nodeToExamine = (HashTableNode*)malloc(sizeof(HashTableNode));

    if (table->table[lookupHashIndex] != NULL){
        
        
        nodeToExamine = table->table[lookupHashIndex]; // FIRST NODE IN THE SLOT
         

        if (strcmp(url, nodeToExamine->url) == 0){
           
            return 0;
        }
        else if (nodeToExamine->next == NULL){ // only one element and it is not the same url
            
            return 1;
        }
       
        if (nodeToExamine->next != NULL){
           

            HashTableNode *currentNode = nodeToExamine->next;

            while (currentNode != NULL)
            {

              if (strcmp(currentNode->url, url) != 0 ){ // different URL 

                    uniqueBool = 0; // changed from 1
               }
               else{
                    uniqueBool = 1; 
                    sameCount++;
               }

                currentNode = currentNode->next;

            } 

            if (uniqueBool == 0 && sameCount == 0) {
            
                return 1;
            }
            else{
                
                return 0; // found it
            }


        }
        else{
            
            return 0; // found it
        }

    }
    else{
        
        return 1; 
    }
}

// free resources
void CleanTable(HashTable* table) {
  
  
  for (int i = 0; i<MAX_HASH_SLOT; i++) {
    
    HashTableNode* n = table->table[i];

    if (n != NULL){
         if (n->url != NULL){
        free(n->url);
        }
    
    }  
    free(n); 
  }
}

int HashTableInsert(HashTable *table, const char *url)
{
    // find collision list starting point
    long int hashindex = JenkinsHash(url, MAX_HASH_SLOT);
    HashTableNode **pp = table->table+hashindex;

    // walk the collision list looking for a match
    while (*pp && strcmp(url, (*pp)->url))
        pp = &(*pp)->next;

    if (!*pp)
    {
        
        // no matching node found. insert a new one.
        HashTableNode *pNew = malloc(sizeof *pNew);
        pNew->url = strdup(url);
        pNew->next = NULL;
        *pp = pNew;
    }
    else
    {   // url already in the table
        
        return 1;
    }
    return 0;
}




