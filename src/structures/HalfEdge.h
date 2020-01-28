#ifndef HALF_EDGE_H
#define HALF_EDGE_H

#include <vector>

#include "OrderedBinaryTree.h"

struct HalfEdge;
struct HalfVertex;
struct HalfVertexData;
struct RootedHalfGraph;

using HalfEdgePtr = std::shared_ptr<HalfEdge>;
using HalfVertexPtr = std::shared_ptr<HalfVertex>;

struct HalfEdge {
    HalfEdgePtr previous;
    HalfEdgePtr next;
    HalfEdgePtr other;

    HalfVertexPtr origin;

    HalfEdge(HalfVertexPtr);
};

struct HalfVertexData {
    int label;
};

struct HalfVertex {
    HalfVertexData data;
    HalfEdgePtr edge;
};

struct RootedHalfGraph {
    std::vector<HalfVertexPtr> vertices;
    std::vector<HalfEdgePtr> edges;
    HalfVertexPtr root;

    RootedHalfGraph(OrderedBinaryTree tree);

    HalfEdgePtr buildFromTree(OrderedBinaryTreeNodePtr, HalfEdgePtr);
};

#endif
