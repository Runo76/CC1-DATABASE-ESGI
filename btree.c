#include "tree.h"
#include <stdlib.h>
#include <string.h>

// Insert a student into the tree
TreeNode* insert_tree(TreeNode* root, Student student) {
    if (root == NULL) {
        TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
        new_node->data = student;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }

    if (student.id < root->data.id) {
        root->left = insert_tree(root->left, student);
    } else if (student.id > root->data.id) {
        root->right = insert_tree(root->right, student);
    }

    return root;
}

// Search for a student by ID
TreeNode* search_tree(TreeNode* root, int id) {
    if (root == NULL || root->data.id == id) {
        return root;
    }

    if (id < root->data.id) {
        return search_tree(root->left, id);
    } else {
        return search_tree(root->right, id);
    }
}
