#ifndef CODEGEN_H
#define CODEGEN_H
#include<strtab.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tree.h"

// Function declarations to process different constructs
int process(tree* node);
void gen_expression(tree* node);
void gen_assignment(tree* node);
void gen_conditional(tree* node);
void gen_loop(tree* node);
void gen_function(tree* node);
void gen_output_function_call(tree* node);

#endif