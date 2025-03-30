#ifndef TREE_H
#define TREE_H

#include <stdio.h>

// Student structure
typedef struct {
    int id;
    char name[50];
    float grade;
} Student;

// Tree node structure
typedef struct TreeNode {
    Student data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Function declarations
TreeNode* insert_tree(TreeNode* root, Student student);
TreeNode* search_tree(TreeNode* root, int id);
TreeNode* delete_tree(TreeNode* root, int id);
void inorder_traversal(TreeNode* root);
void save_tree_to_file(TreeNode* root, FILE* file);
void load_tree_from_file(TreeNode** root, const char* filename);

#endif
