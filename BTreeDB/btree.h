#ifndef BTREE_H
#define BTREE_H
#include "table.h"
#include "persistence.h"
#include <stdio.h>


// Pour mon commit j'Ajoute des fonction btree_update, delete et freeTree

typedef struct BTreeNode {
    Line line;
    struct BTreeNode* left;
    struct BTreeNode* right;
} BTreeNode;

BTreeNode* btree_insert(BTreeNode* node, Line line);
void btree_traverse(BTreeNode* root);
BTreeNode* btree_delete(BTreeNode* root, int id);
void btree_update(BTreeNode* root, int id, char* username, char* email);
void freeTree(BTreeNode* root);

#endif

