#include <random>
#include <chrono>
#include <vector>

#include "RemyBinaryTree.h"

void reconnect(OrderedBinaryTreeNodePtr parent, OrderedBinaryTreeNodePtr old, OrderedBinaryTreeNodePtr connecting) {
    if (parent == nullptr) {
        return;
    }
    if (parent->left == old) {
        parent->left = connecting;
    }
    else {
        parent->right = connecting;
    }
}

OrderedBinaryTree sampleRandomOrderedBinaryTreeRemy(size_t size, long long seed) {
    OrderedBinaryTree result = OrderedBinaryTree{nullptr};
    if (size == 0) {
        return result;
    }
    OrderedBinaryTreeNodePtr root(new OrderedBinaryTreeNode());
    OrderedBinaryTreeNodePtr left(new OrderedBinaryTreeNode(root));
    OrderedBinaryTreeNodePtr right(new OrderedBinaryTreeNode(root));
    root->left = left;
    root->right = right;
    std::vector<OrderedBinaryTreeNodePtr> nodes;
    nodes.push_back(root);
    nodes.push_back(left);
    nodes.push_back(right);

    std::mt19937 rnd(seed);
    std::uniform_int_distribution<> randomBit(0, 1);

    for (unsigned int i = 1; i < size; i++) {
        std::uniform_int_distribution<> randomInt(0, i-1);
        OrderedBinaryTreeNodePtr cut = nodes[randomInt(rnd)];
        OrderedBinaryTreeNodePtr newNode(new OrderedBinaryTreeNode(cut->parent));
        OrderedBinaryTreeNodePtr newLeaf(new OrderedBinaryTreeNode(newNode));
        nodes.push_back(newNode);
        nodes.push_back(newLeaf);
        reconnect(cut->parent, cut, newNode);
        newNode->left = cut;
        newNode->right = newLeaf;
        cut->parent = newNode;
        if (randomBit(rnd)) {
            std::swap(newNode->left, newNode->right);
        }
    }
    for (OrderedBinaryTreeNodePtr node : nodes) {
        if (node->isRoot()) {
            result.root = node;
            break;
        }
    }
    return result;
}