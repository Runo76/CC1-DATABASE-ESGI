#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <stdio.h>


struct BTreeNode;  
typedef struct BTreeNode BTreeNode;

void saveTree(BTreeNode* root, FILE* file);
BTreeNode* loadTree(FILE* file);

#endif

