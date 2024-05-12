#include <chrono>
#include <gtest/gtest.h>

extern "C" {
    #include "func.h"
}

TEST(MAIN_TEST, get_expected14actual14_14Returned) {
    // arrange
    RBNode* root = createNode(20, 20);
    root = insert(root, root);
    balance(&root, root);

    for (int index = 0; index < 40; index++) {
        RBNode* new_node = createNode(index, index);
        new_node = insert(new_node, root);

        balance(&root, new_node);
    }

    // exp
    int expected = 14;

    // act
    int actual = get(root, 14)->value;

    // assert
    ASSERT_EQ(expected, actual);
}


TEST(MAIN_TEST, get_expectedNULLactualNULL_NULLReturned) {
    // arrange
    RBNode* root = createNode(20, 20);
    root = insert(root, root);
    balance(&root, root);

    for (int index = 0; index < 40; index++) {
        RBNode* new_node = createNode(index, index);
        new_node = insert(new_node, root);

        balance(&root, new_node);
    }

    // exp
    void* expected = NULL;

    // act
    void* actual = get(root, 44);

    // assert
    ASSERT_EQ(expected, actual);
}


TEST(MAIN_TEST, removeNode_expectedNULLactualNULL_NULLReturned) {
    // arrange
    RBNode* root = createNode(20, 20);
    root = insert(root, root);
    balance(&root, root);

    for (int index = 0; index < 40; index++) {
        RBNode* new_node = createNode(index, index);
        new_node = insert(new_node, root);

        balance(&root, new_node);
    }

    removeNode(&root, 39);

    // exp
    void* expected = NULL;

    // act
    RBNode* actual = get(root, 39);

    // assert
    ASSERT_EQ(expected, actual);
}


TEST(MAIN_TEST, removeNode_expectedNULLactualNULL_NULLReturned2) {
    // arrange
    RBNode* root = createNode(20, 20);
    root = insert(root, root);
    balance(&root, root);

    for (int index = 0; index < 40; index++) {
        RBNode* new_node = createNode(index, index);
        new_node = insert(new_node, root);

        balance(&root, new_node);
    }

    removeNode(&root, 38);

    // exp
    void* expected = NULL;

    // act
    RBNode* actual = get(root, 38);

    // assert
    ASSERT_EQ(expected, actual);
}



TEST(MAIN_TEST, removeNode_expected38actual38_38Returned) {
    RBNode* root = createNode(20, 20);
    root = insert(root, root);
    balance(&root, root);

    for (int index = 0; index < 40; index++) {
        RBNode* new_node = createNode(index, index);
        new_node = insert(new_node, root);

        balance(&root, new_node);
    }

    removeNode(&root, 39);

    // exp
    int expected = 38;

    // act
    int actual = get(root, 38)->value;

    // assert
    ASSERT_EQ(expected, actual);
}
