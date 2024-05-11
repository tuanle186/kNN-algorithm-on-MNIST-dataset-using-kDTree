#include "kDTree.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */

// Constructor
kDTree::kDTree(int k) : k(k), root(nullptr) {}

// Destructor
kDTree::~kDTree() {
    // Implement destructor
    clearTree(root);
}

// Copy Assignment Operator
const kDTree &kDTree::operator=(const kDTree &other) {
    // Implement copy assignment operator
    if (this != &other) // Check for self-assignment
    {
        k = other.k;
        clearTree(root);
        root = cloneTree(other.root);
    }
    return *this;
}

// Copy Constructor
kDTree::kDTree(const kDTree &other) {
    // Implement copy constructor
    k = other.k;
    root = cloneTree(other.root);
}

// Helper function to recursively clone a tree
kDTreeNode* kDTree::cloneTree(const kDTreeNode *node)
{
    if (node == nullptr)
        return nullptr;
    return new kDTreeNode(node->data, cloneTree(node->left), cloneTree(node->right));
}

// Helper function to recursively delete a tree
void kDTree::clearTree(kDTreeNode *node)
{
    if (node != nullptr)
    {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
}

void kDTree::inorderTraversalHelper(kDTreeNode *node) const {
    if (node == nullptr)
        return;
    
    inorderTraversalHelper(node->left);
    // Process current node (e.g., print or do something with node->data)
    // For example: cout << node->data << " ";
    inorderTraversalHelper(node->right);
}

void kDTree::inorderTraversal() const {
    inorderTraversalHelper(root);
}

void kDTree::preorderTraversalHelper(kDTreeNode *node) const {
    if (node == nullptr)
        return;
    
    // Process current node (e.g., print or do something with node->data)
    // For example: cout << node->data << " ";
    preorderTraversalHelper(node->left);
    preorderTraversalHelper(node->right);
}

void kDTree::preorderTraversal() const {
    preorderTraversalHelper(root);
}

void kDTree::postorderTraversalHelper(kDTreeNode *node) const {
    if (node == nullptr)
        return;
    
    postorderTraversalHelper(node->left);
    postorderTraversalHelper(node->right);
    // Process current node (e.g., print or do something with node->data)
    // For example: cout << node->data << " ";
}

void kDTree::postorderTraversal() const {
    postorderTraversalHelper(root);
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

// Insert a point into the tree
void kDTree::insert(const vector<int> &point) {
    // Implement insertion
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