#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

#include "../../src/generators/RemyBinaryTree.h"
#include "../../src/structures/OrderedBinaryTree.h"

using namespace std;

int get_depth(OrderedBinaryTreeNodePtr root) {
    if (root == nullptr) {
        return 0;
    }
    return max(get_depth(root->left), get_depth(root->right)) + 1;
}

double get_empirical_statistic(size_t count, size_t size, vector<long long> &seeds) {
    double sum = 0;
    for (size_t i = 0; i < count; i++) {
        OrderedBinaryTree tree = sampleRandomOrderedBinaryTreeRemy(size, seeds[i]);
        sum += get_depth(tree.root);
    }
    return sum / count;
}

double get_real_statistic(size_t size) {
    return (double) 2.0 * sqrt(M_PI * size);
}

int main() {
    size_t count, size;
    cin >> count >> size;
    vector<long long> seeds(count);
    for (size_t i = 0; i < count; i++) {
        seeds[i] = i;
    }
    cout << "Empirical: " << get_empirical_statistic(count, size, seeds) << endl;
    cout << "Read: " << get_real_statistic(size) << endl;
    return 0;
}