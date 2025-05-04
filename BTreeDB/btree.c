#include "btree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//également pour mon commit j'Ajoute des fonctionnalité Update et Delete via les fonction BTree_update et btree_delete


BTreeNode* newNode(Line line) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->line = line;
    node->left = node->right = NULL;
    return node;
}

BTreeNode* btree_insert(BTreeNode* node, Line line) {
    if (node == NULL) return newNode(line);

    if (line.id < node->line.id)
        node->left = btree_insert(node->left, line);
    else if (line.id > node->line.id)
        node->right = btree_insert(node->right, line);

    return node;
}

void btree_traverse(BTreeNode* root) {
    if (root == NULL) return;
    btree_traverse(root->left);
    print_line(&root->line);
    btree_traverse(root->right);
}
	



void btree_update(BTreeNode* root, int id, char* username, char* email) {
    if (root == NULL) return;

    if (id == root->line.id) {
        strcpy(root->line.username, username);
        strcpy(root->line.email, email);
      
        return;
    }

    if (id < root->line.id)
        btree_update(root->left, id, username, email);
    else
        btree_update(root->right, id, username, email);
}

BTreeNode* find_min(BTreeNode* node) {
    while (node->left != NULL) node = node->left;
    return node;
}

BTreeNode* btree_delete(BTreeNode* root, int id) {
    if (root == NULL) return root;

    if (id < root->line.id)
        root->left = btree_delete(root->left, id);
    else if (id > root->line.id)
        root->right = btree_delete(root->right, id);
    else {
        if (root->left == NULL) {
            BTreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            BTreeNode* temp = root->left;
            free(root);
            return temp;
        }

        BTreeNode* temp = find_min(root->right);
        root->line = temp->line;
        root->right = btree_delete(root->right, temp->line.id);
    }
    return root;
}



void freeTree(BTreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

