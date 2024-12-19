#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stddef.h>
#include<../src/strtab.h>

/* You should use a linear linklist to keep track of all parameters passed to a function. The working_list_head should point to the beginning of the linklist and working_list_end should point to the end. Whenever a parameter is passed to a function, that node should also be added in this list. */
param *working_list_head = NULL;
param *working_list_end = NULL;

table_node* current_scope = NULL; // A global variable that should point to the symbol table node in the scope tree as discussed in lecture 13 and 14.

void print_sym_tab() {
  printf("TODO: define print_sym_tab()\n");
}

/* TODO: Define remaining functions from strtab.h. */

unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}



int ST_insert(char *id, int data_type, int symbol_type, int* scope){
    
    // Compute the hash value
    int index = hash((unsigned char *)id) % MAXIDS;
    int start = index;

    // Start at the returned hash and probe until we find an empty slot or the scope-id combo
    while (current_scope->strTable[index] != NULL && strcmp(current_scope->strTable[index]->id, id) != 0)
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
    if (current_scope->strTable[index] == NULL)
    {
        printf("Inserting %s at index %d\n", id, index);
        current_scope->strTable[index] = (symEntry*) malloc(sizeof(symEntry));
        current_scope->strTable[index]->id = (id);
        current_scope->strTable[index]->data_type = data_type;
        current_scope->strTable[index]->symbol_type = symbol_type;
        current_scope->strTable[index]->size = 0;
    }
    else{
        // The id is already in the symbol table
        yyerror("Error: The id is already in the symbol table.\n");
    }

    //todo: handle scope
    if(current_scope->parent == NULL)
        *scope = -1;
    else
        *scope = current_scope->parent->numChildren - 1;

    return index;
}


symEntry* ST_lookup(char *id) {
    // Compute the hash value
    int start = hash((unsigned char *)id) % MAXIDS;
     

    table_node* searchScope = current_scope;

    while(searchScope != NULL){
      int index = start;
        while (searchScope->strTable[index] != NULL){
            if(strcmp(searchScope->strTable[index]->id, id) == 0){
                return searchScope->strTable[index];
            }
            index = (index + 1) % MAXIDS;
            if (index == start){
                break;
            }
        }
        searchScope = searchScope->parent;
    }

    return NULL;
    
    
}

void add_param(int data_type, int symbol_type){
    param* new_param = (param*) malloc(sizeof(param));
    new_param->data_type = data_type;
    new_param->symbol_type = symbol_type;
    new_param->next = NULL;

    if(working_list_head == NULL){
        working_list_head = new_param;
        working_list_end = new_param;
    } else {
        working_list_end->next = new_param;
        working_list_end = new_param;
    }
}


void connect_params(int index, int num_params){
    current_scope->parent->strTable[index]->params = working_list_head;
    current_scope->parent->strTable[index]->size = num_params;
    working_list_head = NULL;
    working_list_end = NULL;
    num_params = 0;
}

void new_scope(){
    table_node* scope = (table_node*) malloc(sizeof(table_node));
    scope->numChildren = 0;
    if(current_scope){
        if(current_scope->first_child == NULL){
            current_scope->first_child = scope;
        }
        else{
            current_scope->last_child->next = scope;
        }
        current_scope->last_child = scope;
        current_scope->numChildren++;
        scope->parent = current_scope;
    }
    current_scope = scope;
}

void up_scope(){
    if(current_scope->parent != NULL){
        current_scope = current_scope->parent;
    }
}

void print_sym_entry(symEntry* entry){
    /*printf(entry->id);
    printf(entry->scope);
    printf(entry->data_type);
    printf(entry->symbol_type);
    printf(entry->size); */
}

void print_sym_table(table_node* scope, int depth){
    /*printf("\n\nSYMBOL TABLE:\n");
    for(int i = 0; i < MAXIDS; i++){
        if(scope->strTable[i] != NULL){
            for(int j = 0; j < depth; j++){
                printf("  ");
            }
            printf("%d: ", i);
            print_sym_entry(scope->strTable[i]);
        }
    }
    //todo recursively call print_sym_table on children*/
}

void print_all_sym_tab(){
    /*table_node* scope = current_scope;
    int depth = 0;
    while(scope->parent != NULL){
        scope = scope->parent;
    }
    print_sym_table(scope, depth);*/
}


char* get_symbol_id(int i){
    return current_scope->strTable[i]->id;
}