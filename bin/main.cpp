#include <iostream>
#include "../lib/BST.h"

int main() {
    BST<int> b = {};
    BST<int> bst(b);

    bst = {20, 23};
    bst.insert({1, 2, 3});
    bst.insert(6, 9);
    bst = {50, 25, 30, 35, 40, 27, 26, 12, 3, 75, 80, 79, 36, 38};
    for (auto it = bst.crbegin<TraverseTag::In>(); it != bst.crend<TraverseTag::In>(); ++it) {  std::cout << *it << " "; }
    std::cout << '\n';

    return 0;
}