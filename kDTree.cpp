#include "kDTree.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */

kDTree::kDTree(int k) {
    this->k = k;
    this->root = nullptr;
}

kDTree::~kDTree() {
    clearTree(root);
}

const kDTree &kDTree::operator=(const kDTree &other) {
    if (this != &other) // Check for self-assignment
    {
        k = other.k;
        clearTree(root);
        root = cloneTree(other.root);
    }
    return *this;
}

kDTree::kDTree(const kDTree &other) {
    k = other.k;
    root = cloneTree(other.root);
}

kDTreeNode* kDTree::cloneTree(const kDTreeNode *node)
{
    if (node == nullptr)
        return nullptr;
    return new kDTreeNode(node->data, cloneTree(node->left), cloneTree(node->right));
}


void kDTree::clearTree(kDTreeNode *node)
{
    if (node != nullptr)
    {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
}

void kDTree::inorderTraversalHelper(kDTreeNode *node, bool& isFirst) const {
    if (node == nullptr)
        return;

    inorderTraversalHelper(node->left, isFirst);
    
    if (!isFirst) {
        cout << " ";
    } else {
        isFirst = false;
    }

    cout << "(";
    for (auto it = node->data.begin(); it != node->data.end(); ++it) {
        cout << *it;
        if (it != prev(node->data.end())) {
            cout << ",";
        }
    }
    cout << ")";
    
    inorderTraversalHelper(node->right, isFirst);
}

void kDTree::inorderTraversal() const {
    bool isFirst = true;
    inorderTraversalHelper(root, isFirst);
}

void kDTree::preorderTraversalHelper(kDTreeNode *node, bool& isFirst) const {
    if (node == nullptr)
        return;
    
    if (!isFirst) {
        cout << " ";
    } else {
        isFirst = false;
    }

    cout << "(";
    for (auto it = node->data.begin(); it != node->data.end(); ++it) {
        cout << *it;
        if (it != prev(node->data.end())) {
            cout << ",";
        }
    }
    cout << ")";

    preorderTraversalHelper(node->left, isFirst);
    preorderTraversalHelper(node->right, isFirst);
}

void kDTree::preorderTraversal() const {
    bool isFirst = true;
    preorderTraversalHelper(root, isFirst);
}

void kDTree::postorderTraversalHelper(kDTreeNode *node, bool& isFirst) const {
    if (node == nullptr)
        return;
    
    postorderTraversalHelper(node->left, isFirst);
    postorderTraversalHelper(node->right, isFirst);
    if (!isFirst) {
        cout << " ";
    } else {
        isFirst = false;
    }

    cout << "(";
    for (auto it = node->data.begin(); it != node->data.end(); ++it) {
        cout << *it;
        if (it != prev(node->data.end())) {
            cout << ",";
        }
    }
    cout << ")";
}

void kDTree::postorderTraversal() const {
    bool isFirst = true;
    postorderTraversalHelper(root, isFirst);
}


// Height of the tree
int kDTree::height() const {
    // Implement height calculation
    return 0;
}

// Count of nodes in the tree
int kDTree::nodeCount() const {
    // Implement node count
    return 0;
}

// Count of leaf nodes in the tree
int kDTree::leafCount() const {
    // Implement leaf count
    return 0;
}

void kDTree::insert(const vector<int> &point) {
    root = insertHelper(root, point, 0);
}

kDTreeNode* kDTree::insertHelper(kDTreeNode* node, const vector<int> &point, int depth) {
    // If the current node is null, create a new node with the point
    if (node == nullptr) {
        return new kDTreeNode(point);
    }

    // Calculate the current dimension
    int dim = depth % k;

    // Compare the point's coordinate with the current node's coordinate in the current dimension
    if (point[dim] < node->data[dim]) {
        // Recur for the left subtree
        node->left = insertHelper(node->left, point, depth + 1);
    } else {
        // Recur for the right subtree
        node->right = insertHelper(node->right, point, depth + 1);
    }

    return node;
}

// Remove a point from the tree
void kDTree::remove(const vector<int> &point) {
    // Implement removal
}

// Search for a point in the tree
bool kDTree::search(const vector<int> &point) {
    // Implement search
    return false;
}

// Build the tree from a list of points
void kDTree::buildTree(const vector<vector<int>> &pointList) {
    // Implement tree construction
}

// Find the nearest neighbor to a target point
void kDTree::nearestNeighbour(const vector<int> &target, kDTreeNode *best) {
    // Implement nearest neighbor search
}

// Find the k nearest neighbors to a target point
void kDTree::kNearestNeighbour(const vector<int> &target, int k, vector<kDTreeNode *> &bestList) {
    // Implement k nearest neighbors search
}


kNN::kNN(int k) {

}

void kNN::fit(Dataset &X_train, Dataset &y_train) {

}

Dataset kNN::predict(Dataset &X_test) {
    Dataset myDataset;
    return myDataset;
}

double kNN::score(const Dataset &y_test, const Dataset &y_pred) {
    return 0.0;
}