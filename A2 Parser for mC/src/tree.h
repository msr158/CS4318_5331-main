#ifndef TREE_H
#define TREE_H

#define MAXCHILDREN 12

typedef struct treenode tree;

/* tree node - you may need to add more fields or change this file however you see fit. */
struct treenode {
      int nodeKind;
      int numChildren;
      int val;
      tree *parent;
      tree *children[MAXCHILDREN];
};

extern tree *ast; /* pointer to AST root */

/* builds sub tree with zeor children  */
tree *maketree(int kind);

/* builds sub tree with leaf node. Leaf nodes typically hold a value. */
tree *maketreeWithVal(int kind, int val);

/* assigns the subtree rooted at 'child' as a child of the subtree rooted at 'parent'. Also assigns the 'parent' node as the 'child->parent'. */
void addChild(tree *parent, tree *child);

/* prints the ast recursively starting from the root of the ast. This function prints the warning "undeclared variable" or <nodeKind, value> for identifiers and integers, or <nodeKind, type name> for typeSpecifiers, and <nodeName, the operator symbol> for relational and arithmetic operators. For more information, take a look at the example in the "Sample Output" section of the assignment instructions.*/
void printAst(tree *root, int nestLevel);


#endif
