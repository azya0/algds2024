#include <stdbool.h>
#include <malloc.h>
#include <stdio.h>

#pragma once

typedef struct node {
    int key, value;
    bool isBlack;
    struct node *left, *right, *parent;
} RBNode;


RBNode* createNode(int key, int value);

RBNode* insert(RBNode* _new, RBNode* root);

void leftRotate(RBNode **root, RBNode *current);

void rightRotate(RBNode **root, RBNode *current);

void balance(RBNode **root, RBNode *element);

RBNode* get(RBNode *root, int key);

int countChildren(RBNode *current);

RBNode* getOnlyChild(RBNode *current);

RBNode* getMin(RBNode *current);

void transplantNode(RBNode **root, RBNode *to, RBNode *from);

void balanceAfterDelete(RBNode** root, RBNode *element);

void freeNode(RBNode* toFree);

void removeNode(RBNode** root, int key);
