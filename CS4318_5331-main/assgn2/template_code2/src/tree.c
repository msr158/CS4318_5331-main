#include<tree.h>
#include<strtab.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

 /* string values for ast node types, makes tree output more readable */
char *charnodeNames[33] = {"program", "declList", "decl", "varDecl", "typeSpecifier",
                       "funDecl", "formalDeclList", "formalDecl", "funBody",
                       "localDeclList", "statementList", "statement", "compoundStmt",
                       "assignStmt", "condStmt", "loopStmt", "returnStmt","expression",
                       "relop", "addExpr", "addop", "term", "mulop", "factor",
                       "funcCallExpr", "argList", "integer", "identifier", "var",
                       "arrayDecl", "char", "funcTypeName"};

char *typeNames[3] = {"int", "char", "void"}; // array to hold string representations of data types
char *ops[10] = {"+", "-", "*", "/", "<", "<=", "==", ">=", ">", "!="}; // array to hold string repressentations of common operators 


tree *ast; 

tree *maketree(int kind) {
  tree *this = (tree *) malloc(sizeof(struct treenode));
  this->nodeKind = kind;
  this->numChildren = 0;
  return this;

}

// function to create a new tree node with a given kind (type).
tree *maketreeWithVal(int kind, int val) {
  tree *this = (tree *) malloc(sizeof(struct treenode));
  this->nodeKind = kind;
  this->numChildren = 0;
  this->val = val;
  return this;

}

// function to create a new tree node with a given kind and value.
void addChild(tree *parent, tree *child) {
  if (parent->numChildren == MAXCHILDREN) {
    printf("Cannot add child to parent node\n");
    exit(1);
  }
  /*nextAvailChild(parent) = child;*/
  parent->children[parent->numChildren] = child;
  // child->parent = parent;
  parent->numChildren++;
}

void printAst(tree *node, int nestLevel) {
  if(node == NULL){
    printf("NULL node encountered\n");
    return;
  }
  if(node->nodeKind < 0 || node->nodeKind >= 33){
    printf("Invalid nodeKind: %d\n", node->nodeKind);
    return;
  }
  
  char *nodeName = charnodeNames[node->nodeKind];
  //printf("%s\n", charnodeNames[node->nodeKind]);
  if (strcmp(nodeName, "identifier") == 0) {        //look up table with val
        printf("%s (%d)\n", nodeName, node->val);       //strTable[node->vals],, chnage back to s
    } 
    else if(strcmp(nodeName, "integer") == 0){          
        printf("%s (%d)\n", nodeName, node->val);
    } 
    else if(strcmp(nodeName, "typeSpecifier") == 0){          
        printf("%s (%s)\n", nodeName, typeNames[node->val]);
    }
    else {
        printf("%s\n", nodeName);
    }

  int i, j;

  for (i = 0; i < node->numChildren; i++)  {
    for (j = 0; j < nestLevel; j++) 
      printf("  ");
    printAst(node->children[i], nestLevel + 1);
  }


}
