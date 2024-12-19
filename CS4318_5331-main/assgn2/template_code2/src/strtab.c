#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "strtab.h"

struct strEntry strTable[MAXIDS];

/* Provided is a hash function that you may call to get an integer back. */
unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

// declare an array of strings of data types
const char* types[] = {
    "int", 
    "char",
    "void"
};

// declare an array of strings representing diff symbol type modifiers
const char* symTypeMod[] = {
    "scalar",
    "array",
    "function"
};


int ST_insert(char *id, char *scope, int data_type, int symbol_type){
    // TODO: Concatenate the scope and id and use that to create the hash key
    
    // Concatenate the scope and id to create the hash key
    char *keyStr = (char *)malloc(strlen(scope) + strlen(id) + 1);
    strcpy(keyStr, scope);
    strcat(keyStr, id);

    // Compute the hash value
    int index = hash((unsigned char *)keyStr) % MAXIDS;
    int start = index;
    free(keyStr);

    // Start at the returned hash and probe until we find an empty slot or the scope-id combo
    while (strTable[index].id != NULL && (strcmp(strTable[index].id, id) != 0 || strcmp(strTable[index].scope, scope) != 0))
    {
        index = (index + 1) % MAXIDS;
        if (index == start)
        {
            // The symbol table is full
            fprintf(stderr, "Error: Symbol table is full.\n");
            return -1;
        }
    }

    // If index isn't already used, store the entry there
    if (strTable[index].id == NULL)
    {
        strTable[index].id = strdup(id);
        strTable[index].scope = strdup(scope);
        strTable[index].data_type = data_type;
        strTable[index].symbol_type = symbol_type;
    }


  // TODO: Use ST_lookup to check if the id is already in the symbol table. If yes, ST_lookup will return an index that is not -1. if index != -1, that means the variable is already in the hashtable. Hence, no need to insert that variable again. However, if index == -1, then use linear probing to find an empty spot and insert there. Then return that index.

    return index;
}

int ST_lookup(char *id, char *scope) {
    // TODO: Concatenate the scope and id and use that to create the hash key



    // Concatenate the scope and id to create the hash key
    char *keyStr = (char *)malloc(strlen(scope) + strlen(id) + 1);
    strcpy(keyStr, scope);
    strcat(keyStr, id);

    // Compute the hash value
    int index = hash((unsigned char *)keyStr) % MAXIDS;
    int start = index;
    free(keyStr);

    // Start at index and probe until we either find the scope-id or an empty slot
    while (strTable[index].id != NULL && (strcmp(strTable[index].id, id) != 0 || strcmp(strTable[index].scope, scope) != 0))
    {
        index = (index + 1) % MAXIDS;
        if (index == start)
        {
            // The symbol table is full
            fprintf(stderr, "Error: Symbol table is full.\n");
            return -1;
        }
    }

    // If we stopped probing because of an empty slot and were searching locally, search globally
    if (strTable[index].id == NULL && strcmp(scope, "") != 0)
    {
        index = hash((unsigned char *)id) % MAXIDS;
        while (strTable[index].id != NULL && (strcmp(strTable[index].id, id) != 0 || strcmp(strTable[index].scope, "") != 0))
        {
            index = (index + 1) % MAXIDS;
        }
    }

    if (strTable[index].id == NULL)
    {
        fprintf(stderr, "Warning: undeclared variable\n");
        return -1;
    }



    // TODO: Use the hash value to check if the index position has the "id". If not, keep looking for id until you find an empty spot. If you find "id", return that index. If you arrive at an empty spot, that means "id" is not there. Then return -1. 

    return index;
}

void output_entry(int i){
    printf("%d: %s ", i, types[strTable[i].data_type]);
    printf("%s:%s%s\n", strTable[i].scope, strTable[i].id, symTypeMod[strTable[i].symbol_type]);
}

