#include <stdbool.h>
#include <malloc.h>
#include <stdio.h>

typedef struct node {
    int key, value;
    bool isBlack;
    struct node *left, *right, *parent;
} RBNode;


RBNode* createNode(int key, int value) {
    RBNode *result = malloc(sizeof(RBNode));
    
    result->key = key;
    result->value = value;
    result->isBlack = false;
    result->left = result->right = NULL;

    return result;
}


void insert(RBNode* new, RBNode* root) {
    if (new == root) {
        new->isBlack = true;
        return;
    }

    RBNode* current = root;

    while (true) {
        if (current->key < new->key) {
            if (current->left == NULL) {
                current->left = new;
                new->parent = current;
                break;
            }
            current = current->left;
        } else if (current->key > new->key) {
            if (current->right == NULL) {
                current->right = new;
                new->parent = current;
                break;
            }
            current = current->right;
        }
    }
}


void rightRotate(RBNode **root, RBNode *current) {
    RBNode *left = current->left;
    current->left = left->right;

    if (current->left)
        current->left->parent = current;

    left->parent = current->parent;
    if (!current->parent)
        (*root) = left;
    else if (current == current->parent->left)
        current->parent->left = left;
    else
        current->parent->right = left;
    
    left->right = current;
    current->parent = left;
}


void leftRotate(RBNode **root, RBNode *current) {
    RBNode *right = current->right;
    current->right = right->left;

    if (current->right)
        current->right->parent = current;

    right->parent = current->parent;
    if (!current->parent)
        (*root) = right;
    else if (current == current->parent->left)
        current->parent->left = right;
    else
        current->parent->right = right;
    
    right->left = current;
    current->parent = right;
}


void balance(RBNode *root, RBNode *current) {
    RBNode *parent_current = NULL;
    RBNode *grand_parent_current = NULL;
 
    while ((current != root) && (!current->isBlack) && (!current->parent->isBlack)) {
        parent_current = current->parent;
        grand_parent_current = current->parent->parent;
 
        if (parent_current == grand_parent_current->left) {
            RBNode *uncle_current = grand_parent_current->right;
 
            if (uncle_current != NULL && !uncle_current->isBlack) {
                grand_parent_current->isBlack = false;
                parent_current->isBlack = true;
                uncle_current->isBlack = true;
                current = grand_parent_current;
            }
 
            else {
                if (current == parent_current->right) {
                    leftRotate(&root, parent_current);
                    current = parent_current;
                    parent_current = current->parent;
                }

                rightRotate(&root, grand_parent_current);
                bool color = parent_current->isBlack;
                parent_current->isBlack = grand_parent_current->isBlack;
                grand_parent_current->isBlack = color;
                current = parent_current;
            }
        }

        else {
            RBNode *uncle_current = grand_parent_current->left;
 
            if ((uncle_current != NULL) && (!uncle_current->isBlack)) {
                grand_parent_current->isBlack = false;
                parent_current->isBlack = true;
                uncle_current->isBlack = true;
                current = grand_parent_current;
            }

            else {
                if (current == parent_current->left) {
                    rightRotate(&root, parent_current);
                    current = parent_current;
                    parent_current = current->parent;
                }
 
                leftRotate(&root, grand_parent_current);
                bool color = parent_current->isBlack;
                parent_current->isBlack = grand_parent_current->isBlack;
                grand_parent_current->isBlack = color;
                current = parent_current;
            }
        }
    }
}

void print(struct node* root) {
    if (root == NULL)
        return;
    
    print(root->left);

    printf("%d:%d", root->key, root->value);

    print(root->right);
}

int main() {
    RBNode* root = createNode(20, 20);
    insert(root, root);

    for (int index = 0; index < 40; index++) {
        RBNode* new_node = createNode(index, index);
        insert(new_node, root);

        balance(root, new_node);
    }

    // print(root);
}
