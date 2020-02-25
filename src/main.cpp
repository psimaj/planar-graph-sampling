#include <iostream>

#include "./generators/RemyBinaryTree.h"
#include "./structures/structures.h"
#include "./bijections/bijections.h"

void parenthesesTraversal(OrderedBinaryTreeNodePtr node) {
    if (node == nullptr) {
        return;
    }
    std::cout << '(';
    parenthesesTraversal(node->left);
    parenthesesTraversal(node->right);
    std::cout << ')';
}

void countingTraversal(RootedHalfGraph &graph) {
    HalfEdgePtr startingEdge = graph.root->edge;
    HalfEdgePtr currentEdge = startingEdge->next;
    int visitedEdges = 1;
    while (currentEdge != startingEdge) {
        visitedEdges++;
        currentEdge = currentEdge->next;
    }
    std::cout << visitedEdges << std::endl;
}

int main() {
    OrderedBinaryTree tree = sampleRandomOrderedBinaryTreeRemy(3, 0);
    parenthesesTraversal(tree.root);
    std::cout << std::endl;
    RootedHalfGraph graph(tree);
    std::cout << graph.vertices.size() << ' ' << graph.edges.size() << std::endl;
    countingTraversal(graph);
    binaryTreeToIrreducibleDissection(graph);
    countingTraversal(graph);
    return 0;
}