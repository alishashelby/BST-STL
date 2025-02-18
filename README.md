# Binary Search Tree (BST) - STL Container

## Overview

An STL-compliant implementation of a Binary Search Tree container supporting inorder, preorder, and postorder traversals via customizable iterators.

## Features

**STL Compatibility**:
  - [AssociativeContainer](https://en.cppreference.com/w/cpp/named_req/AssociativeContainer)
  - [ReversibleContainer](https://en.cppreference.com/w/cpp/named_req/ReversibleContainer)
  - [AllocatorAwareContainer](https://en.cppreference.com/w/cpp/named_req/AllocatorAwareContainer)
  - [BidirectionalIterator](https://en.cppreference.com/w/cpp/named_req/BidirectionalIterator)

**Traversal Strategies**:
  - Inorder, Preorder, Postorder traversal support via **Tag Dispatch Idiom**

## Testing

All specified requirements are verified through comprehensive test coverage using the [Google Test](https://github.com/google/googletest) framework.

## Example Usage

```cpp
BST<int> bst;
bst = ({15, 5, 16, 18, 17, 8, 3, 11, 7, 9, 6, 12, 13, 10, 0});

std::cout << "Inorder: ";
for(auto it = bst.begin<TraverseTag::In>(); it != bst.end<TraverseTag::In>(); ++it) {
    std::cout << *it << " "; // 0 3 5 6 7 8 9 10 11 12 13 15 16 17 18 
}

std::cout << "\nPreorder: ";
for(auto it = bst.begin<TraverseTag::Pre>(); it != bst.end<TraverseTag::Pre>(); ++it) {
    std::cout << *it << " "; // 15 5 3 0 8 7 6 11 9 10 12 13 16 18 17 
}

std::cout << "\nPost-order: ";
for(auto it = bst.begin<TraverseTag::Post>(); it != bst.end<TraverseTag::Post>(); ++it) {
    std::cout << *it << " "; // 0 3 6 7 10 9 13 12 11 8 5 17 18 16 15 
}
```