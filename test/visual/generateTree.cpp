#include <iostream>
#include <chrono>

#include "../../src/generators/RemyBinaryTree.h"
#include "../../src/utils/conversion.h"
#include "../../src/structures/HalfEdge.h"

using namespace std;

void printAdjacencyList(vector<vector<int>> &adj) {
    int edges = 0;
    for (unsigned int i = 1; i < adj.size(); i++) {
        edges += adj[i].size();
    }
    cout << adj.size() - 1 << ' ' << edges << endl;
    for (unsigned int i = 1; i < adj.size(); i++) {
        for (unsigned int j = 0; j < adj[i].size(); j++) {
            cout << i << ' ' << adj[i][j] << '\n';
        }
    }
}

int main() {
    int n;
    cin >> n;
    long long seed = chrono::system_clock::now().time_since_epoch().count();
    OrderedBinaryTree tree = sampleRandomOrderedBinaryTreeRemy(n, seed);
    RootedHalfGraph halfTree(tree);
    vector<vector<int>> adj = halfGraphToAdjacencyList(halfTree);
    printAdjacencyList(adj);
}