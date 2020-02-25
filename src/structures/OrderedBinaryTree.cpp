#include "OrderedBinaryTree.h"

OrderedBinaryTreeNode::OrderedBinaryTreeNode(OrderedBinaryTreeNodePtr _parent) 
    : left(nullptr), right(nullptr) {
    parent = _parent;
}

bool OrderedBinaryTreeNode::isRoot() {
    return parent == nullptr;
}

bool OrderedBinaryTreeNode::isLeaf() {
    return left == nullptr && right == nullptr;
}
