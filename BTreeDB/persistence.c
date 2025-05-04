#include "persistence.h"
#include "btree.h"
#include <stdlib.h>
#include <string.h>

void saveTree(BTreeNode* root, FILE* file) {
    if (root == NULL) return;

    fwrite(&root->line, sizeof(Line), 1, file);
    saveTree(root->left, file);
    saveTree(root->right, file);
}

BTreeNode* loadTree(FILE* file) {
    Line line;
    BTreeNode* root = NULL;

    while (fread(&line, sizeof(Line), 1, file)) {
        root = btree_insert(root, line);
    }

    return root;
}

