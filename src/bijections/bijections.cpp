#include <utility>
#include <iostream>

#include "bijections.h"
#include "../structures/structures.h"
#include "../utils/DoublyLinkedList.h"

void reconnectToHexagonVertex(HalfVertexPtr stem, HalfVertexPtr hexagonVertex) {
    stem->edge->origin = hexagonVertex;
    stem->edge->previous = hexagonVertex->edge->previous;
    hexagonVertex->edge->previous->next = stem->edge;
    stem->edge->other->next = hexagonVertex->edge;
    hexagonVertex->edge->previous = stem->edge->other;
}

void binaryTreeToIrreducibleDissection(RootedHalfGraph &tree) {
    DoublyLinkedList<std::pair<HalfVertexPtr, int>> stems;
    HalfEdgePtr currentEdge = tree.root->edge;
    do {
        if (currentEdge->origin->isLeaf()) {
            stems.insertAfter(std::make_pair(currentEdge->origin, 0));
            stems.goNext();
        }
        else {
            stems.data().second++;
        }
        currentEdge = currentEdge->previous;
    } while (currentEdge != tree.root->edge);
    for (size_t i = stems.size(); i > 0 && stems.size() > 0; i--, stems.goPrevious()) {
        while (stems.size() > 0 && stems.data().second > 3) {
            HalfEdgePtr outer = stems.data().first->edge;
            HalfEdgePtr inner = stems.data().first->edge->other;
            HalfEdgePtr firstOnCycle = inner->previous->previous->previous;
            outer->origin = firstOnCycle->origin;
            outer->previous = firstOnCycle->previous;
            firstOnCycle->previous->next = outer;
            firstOnCycle->previous = inner;
            inner->next = firstOnCycle;
            int nonleavesLeft = stems.data().second - 3;
            stems.remove();
            if (stems.size() > 0) {
                stems.data().second += nonleavesLeft;
            }
        }
    }
    std::vector<HalfVertexPtr> hexagon;
    for (size_t i = 0; i < 6; i++) {
        HalfVertexPtr newVertex = tree.addVertex();
        HalfEdgePtr newEdge = tree.addEdge(newVertex);
        newVertex->edge = newEdge;
        hexagon.push_back(newVertex);
    }
    for (size_t i = 0; i < 6; i++) {
        HalfEdgePtr newEdge = tree.addEdge(hexagon[(i+5) % 6]);
        newEdge->other = hexagon[i]->edge;
        hexagon[i]->edge->other = newEdge;
        hexagon[i]->edge->next = hexagon[(i+5) % 6]->edge;
        hexagon[i]->edge->previous = hexagon[(i+1) % 6]->edge;
    }
    for (size_t i = 0; i < 6; i++) {
        hexagon[i]->edge->other->next = hexagon[(i+1) % 6]->edge->other;
        hexagon[i]->edge->other->previous = hexagon[(i+5) % 6]->edge->other;
    }
    size_t hexagonVertexIndex = 0;
    while (stems.size() > 0) {
        reconnectToHexagonVertex(stems.data().first, hexagon[hexagonVertexIndex]);
        hexagonVertexIndex += 3 - stems.data().second;
        hexagonVertexIndex %= 6;
        stems.remove();
        if (stems.size() > 0) {
            stems.goNext();
        }
    }
    tree.root = hexagon[0];
}

void irreducibleDissectionToQuadrangulation(RootedHalfGraph &dissection) {
    HalfVertexPtr firstEnd = dissection.root, otherEnd = dissection.root->edge->other->previous->previous->origin;
    HalfEdgePtr to = dissection.addEdge(firstEnd);
    HalfEdgePtr from = dissection.addEdge(otherEnd);

    to->other = from;
    from->other = to;

    to->next = otherEnd->edge->previous->other;
    otherEnd->edge->previous->other->previous = to;
    to->previous = firstEnd->edge->other;
    firstEnd->edge->other->next = to;

    from->next = firstEnd->edge->previous->other;
    firstEnd->edge->previous->other->previous = from;
    from->previous = otherEnd->edge->other;
    otherEnd->edge->other->next = from;

    dissection.root->edge = to;
}