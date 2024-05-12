#include <stdio.h>
#include "source/func.h"


int main() {
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
    printf("%d", actual);
}
