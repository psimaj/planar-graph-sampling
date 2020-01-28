#include "HalfEdge.h"
#include "OrderedBinaryTree.h"

HalfEdge::HalfEdge(HalfVertexPtr _origin) : origin(_origin) {}

RootedHalfGraph::RootedHalfGraph(OrderedBinaryTree tree) : root(new HalfVertex) {
    vertices.push_back(root);
    HalfEdgePtr downEdge(new HalfEdge(root));
    edges.push_back(downEdge);
    root->edge = downEdge;
    HalfEdgePtr upEdge = buildFromTree(tree.root, downEdge);
    upEdge->next = downEdge;
    downEdge->previous = upEdge;
}

HalfEdgePtr RootedHalfGraph::buildFromTree(OrderedBinaryTreeNodePtr node, HalfEdgePtr previousEdge) {
    HalfVertexPtr currentVertex(new HalfVertex);
    vertices.push_back(currentVertex);
    HalfEdgePtr upEdge(new HalfEdge(currentVertex));
    edges.push_back(upEdge);
    upEdge->other = previousEdge;
    previousEdge->other = upEdge;
    if (node->isLeaf()) {
        upEdge->previous = previousEdge;
        previousEdge->next = upEdge;
    }
    else {
        HalfEdgePtr rightDownEdge(new HalfEdge(currentVertex));
        edges.push_back(rightDownEdge);
        rightDownEdge->previous = previousEdge;
        previousEdge->next = rightDownEdge;
        HalfEdgePtr rightUpEdge = buildFromTree(node->right, rightDownEdge);

        HalfEdgePtr leftDownEdge(new HalfEdge(currentVertex));
        edges.push_back(leftDownEdge);
        leftDownEdge->previous = rightUpEdge;
        rightUpEdge->next = leftDownEdge;
        HalfEdgePtr leftUpEdge = buildFromTree(node->left, leftDownEdge);

        upEdge->previous = leftUpEdge;
        leftUpEdge->next = upEdge;
    }
    return upEdge;
}