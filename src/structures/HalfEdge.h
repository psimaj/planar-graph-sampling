#pragma once

#include <vector>

#include "OrderedBinaryTree.h"

struct HalfEdge;
struct HalfVertex;
struct HalfVertexData;
struct RootedHalfGraph;

using HalfEdgePtr = HalfEdge*;
using HalfVertexPtr = HalfVertex*;

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

    bool isLeaf();
};

struct RootedHalfGraph {
    std::vector<HalfVertexPtr> vertices;
    std::vector<HalfEdgePtr> edges;
    HalfVertexPtr root;

    RootedHalfGraph(OrderedBinaryTree &tree);

    HalfVertexPtr addVertex();
    void removeVertex(size_t);
    HalfEdgePtr addEdge(HalfVertexPtr = nullptr);
    HalfEdgePtr buildFromTree(OrderedBinaryTreeNodePtr, HalfEdgePtr);
};