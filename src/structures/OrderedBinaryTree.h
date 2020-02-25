#ifndef ORDERED_BINARY_TREE_H
#define ORDERED_BINARY_TREE_H

#include <memory>

struct OrderedBinaryTree;
struct OrderedBinaryTreeNode;

using OrderedBinaryTreeNodePtr = OrderedBinaryTreeNode*;

struct OrderedBinaryTreeNode {
    OrderedBinaryTreeNodePtr parent;
    OrderedBinaryTreeNodePtr left;
    OrderedBinaryTreeNodePtr right;

    OrderedBinaryTreeNode(OrderedBinaryTreeNodePtr = nullptr);

    bool isRoot();
    bool isLeaf();
};

struct OrderedBinaryTree {
    OrderedBinaryTreeNodePtr root;
};

#endif
