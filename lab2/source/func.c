#include "func.h"

RBNode* createNode(int key, int value) {
    RBNode *result = malloc(sizeof(RBNode));
    
    result->key = key;
    result->value = value;
    result->isBlack = false;
    result->parent = NULL;
    result->left = result->right = NULL;

    return result;
}

RBNode* insert(RBNode* _new, RBNode* root) {
    if (_new == root)
        return _new;

    RBNode* current = root;

    while (true) {
        if (current->key > _new->key) {
            if (current->left == NULL) {
                current->left = _new;
                _new->parent = current;
                return current;
            }
            current = current->left;
        } else if (current->key < _new->key) {
            if (current->right == NULL) {
                current->right = _new;
                _new->parent = current;
                return current;
            }
            current = current->right;
        } else {
            current->value = _new->value;
            return current;
        }
    }
}

void leftRotate(RBNode **root, RBNode *current) {
    RBNode *right = current->right;
    current->right = right->left;

    if (current->right)
        current->right->parent = current;

    right->parent = current->parent;

    if (current->parent == NULL)
        (*root) = right;
    else if (current == current->parent->left)
        current->parent->left = right;
    else
        current->parent->right = right;
    
    right->left = current;
    current->parent = right;
}

void rightRotate(RBNode **root, RBNode *current) {
    RBNode *left = current->left;
    current->left = left->right;

    if (current->left)
        current->left->parent = current;

    left->parent = current->parent;

    if (current->parent == NULL)
        (*root) = left;
    else if (current == current->parent->left)
        current->parent->left = left;
    else
        current->parent->right = left;
    
    left->right = current;
    current->parent = left;
}

void balance(RBNode **root, RBNode *element) {
    if ((*root) == element) {
        (*root)->isBlack = true;
        return;
    }
    
    RBNode *uncle;

    while ((element != *root) && (!element->parent->isBlack)) {
        if (element->parent == element->parent->parent->left) {
            uncle = element->parent->parent->right;

            if ((uncle != NULL) && (!uncle->isBlack)) {
                element->parent->isBlack = true;
                uncle->isBlack = true;
                element->parent->parent->isBlack = false;
                element = element->parent->parent;
            } else {
                if (element == element->parent->right) {
                    element = element->parent;
                    leftRotate(root, element);
                }

                element->parent->isBlack = true;
                element->parent->parent->isBlack = false;
                rightRotate(root, element->parent->parent);
            }
        } else {
            uncle = element->parent->parent->left;

            if ((uncle != NULL) && (!uncle->isBlack)) {
                element->parent->isBlack = true;
                uncle->isBlack = true;
                element->parent->parent->isBlack = false;
                element = element->parent->parent;
            } else {
                if (element == element->parent->left) {
                    element = element->parent;
                    rightRotate(root, element);
                }

                element->parent->isBlack = true;
                element->parent->parent->isBlack = false;
                leftRotate(root, element->parent->parent);
            }
        }
    }

    (*root)->isBlack = true;
}

RBNode* get(RBNode *root, int key) {
    RBNode *current = root;

    while ((current != NULL) && (current->key != key)) {
        if (key > current->key)
            current = current->right;
        else
            current = current->left;
    }

    return current;
}

int countChildren(RBNode *current) {
    int result = 0;

    if (current->left != NULL)
        result++;
    if (current->right != NULL)
        result++;
    
    return result;
}

RBNode* getOnlyChild(RBNode *current) {
    return (current->left == NULL) ? current->right : current->left;
}

RBNode* getMin(RBNode *current) {
    while (current->left != NULL)
        current = current->left;
    
    return current;
}

void transplantNode(RBNode **root, RBNode *to, RBNode *from) {
    if (to == *root)
        *root = from;
    else if (to == to->parent->left)
        to->parent->left = from;
    else
        to->parent->right = from;
    
    from->parent = to->parent;
}

void balanceAfterDelete(RBNode** root, RBNode *element) {
    while ((element != *root) && (element->isBlack)) {
        RBNode *brother;

        if (element == element->parent->left) {
            brother = element->parent->right;

            if (!brother->isBlack) {
                brother->isBlack = true;
                element->parent->isBlack = false;
                leftRotate(root, element->parent);
                brother = element->parent->right;
            }

            if ((brother->left == NULL || brother->left->isBlack) && (brother->right == NULL || brother->right->isBlack)) {
                brother->isBlack = false;
                element = element->parent;
            } else {
                if (brother->right == NULL || brother->right->isBlack) {
                    brother->left->isBlack = true;
                    brother->isBlack = false;
                    rightRotate(root, brother);
                    brother = element->parent->right;
                }

                brother->isBlack = element->parent->isBlack;
                element->parent->isBlack = true;
                brother->right->isBlack = true;
                leftRotate(root, element->parent);
                element = *root;
            }
        } else {
            brother = element->parent->left;
            
            if ((brother != NULL) && (!brother->isBlack)) {
                brother->isBlack = true;
                element->parent->isBlack = false;
                rightRotate(root, element->parent);
                brother = element->parent->left;
            }

            if ((brother->left == NULL || brother->left->isBlack) && (brother->right == NULL || brother->right->isBlack)) {
                rightRotate(root, element->parent);
                brother = element->parent->left;
            } else {
                if (brother->left == NULL || brother->left->isBlack) {
                    brother->right->isBlack = true;
                    brother->isBlack = false;
                    leftRotate(root, brother);
                    brother = element->parent->left;
                }

                brother->isBlack = element->parent->isBlack;
                element->parent->isBlack = true;
                brother->left->isBlack = true;
                rightRotate(root, element->parent);
                element = *root;
            }
        }
    }

    element->isBlack = true;
}

void freeNode(RBNode* toFree) {
    if (toFree->parent != NULL) {
        if (toFree->parent->left == toFree)
            toFree->parent->left = NULL;
        else
            toFree->parent->right = NULL;  
    }

    free(toFree);
}

void removeNode(RBNode** root, int key) {
    RBNode *toDelete = get(*root, key);

    if (toDelete == NULL)
        return;

    bool isRemoveColorBlack = toDelete->isBlack;

    RBNode* child;
    bool deleteChild = false;

    if (countChildren(toDelete) < 2) {
        child = getOnlyChild(toDelete);
    
        if (child == NULL) {
            child = malloc(sizeof(RBNode));
            child->parent = toDelete;
            child->isBlack = true;
            deleteChild = true;
        }

        transplantNode(root, toDelete, child);
    } else {
        RBNode *minNode = getMin(toDelete->right);
        toDelete->key = minNode->key;
        toDelete->value = minNode->value;
        isRemoveColorBlack = minNode->isBlack;

        child = getOnlyChild(minNode);

        if (child == NULL) {
            child = malloc(sizeof(RBNode));
            child->parent = toDelete;
            child->isBlack = true;
            deleteChild = true;
        }

        transplantNode(root, minNode, child);
    }

    if (isRemoveColorBlack)
        balanceAfterDelete(root, child);

    if (deleteChild) {
        if (child->parent->left == child)
            child->parent->left = NULL;
        else
            child->parent->right = NULL;

        free(child);
    }
}
