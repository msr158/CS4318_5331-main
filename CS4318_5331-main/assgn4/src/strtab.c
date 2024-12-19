#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"strtab.h"

/* extern from strtab.h */
struct strEntry strTable[MAXIDS];

char *symTypeMod[3] = {"", "[]", "()"};
char* types[3] = {"int", "char", "void"};

// djb2 hash function taken from http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int ST_insert(char *id, char *scope, int data_type, int symbol_type){
    printf("Looking up %s in scope %s\n", id, scope);
    // Concatenate the scope and id and use that to create the hash key
    char* keyStr = (char*) malloc(strlen(scope) + strlen(id) + 1);
    strcpy(keyStr, scope);
    strcat(keyStr, id);
    int index = hash(keyStr) % MAXIDS;
    int start = index;
    free(keyStr);

    // Start at the returned hash and probe until we find an empty slot or the scope id combo.
    while (strTable[index].id != NULL && (strcmp(strTable[index].id, id) != 0 || strcmp(strTable[index].scope, scope) != 0)){
        // Just do basic linear probing for now. Not ideal, but it'll work.
        index = (index + 1)%MAXIDS;
        if(index == start)
        {
            yyerror("Symbol table is full.");
            return -1;
        }
    }
    // If index isn't already used, store string there.
    if (strTable[index].id == NULL){
        strTable[index].id = id;
        strTable[index].scope = scope;
        strTable[index].data_type = data_type;
        strTable[index].symbol_type = symbol_type;
    }
    return index;
}

int ST_lookup(char *id, char *scope) {
    printf("Looking up %s in scope %s\n", id, scope);
    // Concatenate the scope and id and use that to create the hash key
    char* keyStr = (char*) malloc(strlen(scope) + strlen(id) + 1);
    strcpy(keyStr, scope);
    strcat(keyStr, id);
    int index = hash(keyStr) % MAXIDS;
    int start = index;
    free(keyStr);

    // Start at index and probe until we either find the scope id or an empty slot.
    while (strTable[index].id != NULL && (strcmp(strTable[index].id, id) != 0 || strcmp(strTable[index].scope, scope) != 0)){
        index = (index + 1)%MAXIDS;
        if(index == start)
        {
            yyerror("Symbol table is full.");
            return -1;
        }
    }

    // If we stopped probing because of a empty slot and were searching locally, search globally.
    if (strTable[index].id == NULL && strcmp(scope,"") != 0){
        index = hash(id) % MAXIDS;
        while (strTable[index].id != NULL && (strcmp(strTable[index].id, id) != 0 || strcmp(strTable[index].scope, "") != 0)){
            index = (index + 1)%MAXIDS;
            // Don't need to worry about a full table here.
            // This search only happens if there's an empty spot.
        }
    }

    if (strTable[index].id == NULL){
        yywarning("undeclared variable");
        index = -1;
    }

    return index;
}

void print_sym_tab(){
    printf("\n\nSYMBOL TABLE:\n");
        for(int i = 0; i < MAXIDS; i++){
            if(strTable[i].id != NULL){
                output_entry(i);
            }
        }
}

void output_entry(int i){
    printf("%d: %s ", i, types[strTable[i].data_type]);
    printf("%s:%s%s\n", strTable[i].scope, strTable[i].id, symTypeMod[strTable[i].symbol_type]);
}
