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

int kDTree::height() const {
    return heightHelper(root);
}

int kDTree::heightHelper(kDTreeNode *node) const {
    if (node == nullptr)
        return 0;
    return 1 + max(heightHelper(node->left), heightHelper(node->right));
}

int kDTree::nodeCount() const {
    return nodeCountHelper(root);
}

int kDTree::nodeCountHelper(kDTreeNode *node) const {
    if (node == nullptr)
        return 0;
    return 1 + nodeCountHelper(node->left) + nodeCountHelper(node->right);
}

int kDTree::leafCount() const {
    return leafCountHelper(root);
}

int kDTree::leafCountHelper(kDTreeNode *node) const {
    if (node == nullptr)
        return 0;
    if (node->left == nullptr && node->right == nullptr)
        return 1;
    return leafCountHelper(node->left) + leafCountHelper(node->right);
}

void kDTree::insert(const vector<int> &point) {
    if (point.size() != k) {
        return;
    }
    root = insertHelper(root, point, 0);
}

kDTreeNode* kDTree::insertHelper(kDTreeNode* node, const vector<int> &point, int depth) {
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

void kDTree::remove(const vector<int> &point) {
    if (point.size() != k) {
        return;
    }
    root = removeHelper(root, point, 0);
}

kDTreeNode* kDTree::removeHelper(kDTreeNode* node, const vector<int> &point, int depth) {
    // If the current node is null, return null
    if (node == nullptr)
        return nullptr;
    
    // Calculate the current dimension
    int dim = depth % k;
    
    // Recursively search for the node containing the point
    if (point == node->data) { // Node found
        // Case 1: Node is a leaf
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        } 
        // Case 2: Node has a right subtree
        else if (node->right != nullptr) {
            // Find replacement node r in u.right
            kDTreeNode* replacementNode = findReplacementNode(node->right, depth + 1, dim);
            
            // Overwrite  u's point
            node->data = replacementNode->data;

            // Remove replacementNode
            node->right = removeHelper(node->right, replacementNode->data, depth + 1);
        } 
        // Case 3: Node has a left subtree
        else {
            // Find replacement node r in u.left
            kDTreeNode* replacementNode = findReplacementNode(node->left, depth + 1, dim);

            // Overwrite u's point
            node->data = replacementNode->data;

            // Move left subtree of u to become right subtree of u
            node->right = node->left;
            node->left = nullptr;

            // Remove replacement node
            node->right = removeHelper(node->right, replacementNode->data, depth + 1);
        }
    } else {
        // Recursively search in the appropriate subtree
        if (point[dim] < node->data[dim]) {
            node->left = removeHelper(node->left, point, depth + 1);
        } else {
            node->right = removeHelper(node->right, point, depth + 1);
        }
    }
    
    return node;
}

kDTreeNode* kDTree::findReplacementNode(kDTreeNode* node, int depth, int alpha) {
    if (node == nullptr) {
        return nullptr; // If the tree is empty, return nullptr
    }

    int dim = depth % k; // Determine the dimension to split on based on the depth

    if (dim == alpha) {
        // If the node is split by alpha dimension
        if (node->left != nullptr) {
            // Continue recursively to the bottom of the left subtree
            return findReplacementNode(node->left, depth + 1, alpha);
        } else {
            // If the left subtree is NULL, return the current node
            return node;
        }
    } else {
        // If the node is split by a dimension other than alpha
        kDTreeNode* minNode = node;

        // Recursively traverse both subtrees
        if (node->left != nullptr) {
            kDTreeNode* leftMin = findReplacementNode(node->left, depth + 1, alpha);
            if (leftMin != nullptr && leftMin->data[alpha] < minNode->data[alpha]) {
                minNode = leftMin;
            }
        }
        if (node->right != nullptr) {
            kDTreeNode* rightMin = findReplacementNode(node->right, depth + 1, alpha);
            if (rightMin != nullptr && rightMin->data[alpha] < minNode->data[alpha]) {
                minNode = rightMin;
            }
        }

        // Check if the current node has a smaller value along the alpha axis
        if (node->data[alpha] < minNode->data[alpha]) {
            minNode = node;
        }

        return minNode;
    }
}

bool kDTree::search(const vector<int> &point) {
    if (point.size() != k) {
        return false;
    }
    return searchHelper(root, point, 0);
}

bool kDTree::searchHelper(kDTreeNode* node, const vector<int> &point, int depth) {
    // If the current node is null, the point doesn't exist in the tree
    if (node == nullptr) {
        return false;
    }

    // Calculate the dimension to split on based on the depth
    int dim = depth % k;

    // If the current node's point is equal to the search point, return true
    if (node->data == point) {
        return true;
    }

    // Compare the current dimension of the node to the search point's dimension
    if (point[dim] < node->data[dim]) {
        // If the search point is less than the current node's point in the current dimension,
        // search in the left subtree
        return searchHelper(node->left, point, depth + 1);
    } else {
        // If the search point is greater than or equal to the current node's point in the current dimension,
        // search in the right subtree
        return searchHelper(node->right, point, depth + 1);
    }
}
 
void kDTree::merge(vector<vector<int>>& arr, int l, int m, int r, int dim) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<vector<int>> L(arr.begin() + l, arr.begin() + l + n1);
    vector<vector<int>> R(arr.begin() + m + 1, arr.begin() + m + 1 + n2);

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i][dim] <= R[j][dim]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void kDTree::mergeSort(vector<vector<int>>& arr, int l, int r, int dim) {
    if (l >= r) {
        return;
    }
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m, dim);
    mergeSort(arr, m + 1, r, dim);
    merge(arr, l, m, r, dim);
}

void kDTree::buildTree(const vector<vector<int>>& pointList) {
    root = buildTreeHelper(pointList, 0);
}

kDTreeNode* kDTree::buildTreeHelper(const vector<vector<int>>& points, int depth) {
    if (points.empty()) {
        return nullptr;
    }

    // Determine current dimension to split on
    int dim = depth % k;

    // Sort points along current dimension using merge sort
    mergeSort(const_cast<vector<vector<int>>&>(points), 0, points.size() - 1, dim);

    for (const auto& point : points) {
        // Print each point
        std::cout << "(";
        for (size_t i = 0; i < point.size(); ++i) {
            std::cout << point[i];
            if (i < point.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << ")";
    }
    cout << endl;
    
    // Find median index
    int medianIndex = points.size() / 2;

    if (points.size() % 2 == 0 && medianIndex > 0) {
        medianIndex--;
    }

    // Create node with median point
    kDTreeNode* node = new kDTreeNode(points[medianIndex]);

    // Recursively build left and right subtrees
    node->left = buildTreeHelper(vector<vector<int>>(points.begin(), points.begin() + medianIndex), depth + 1);
    node->right = buildTreeHelper(vector<vector<int>>(points.begin() + medianIndex + 1, points.end()), depth + 1);

    return node;
}

// Find the nearest neighbor to a target point
void kDTree::nearestNeighbour(const vector<int> &target, kDTreeNode *best) {
    // Implement nearest neighbor search
}

// Find the k nearest neighbors to a target point
void kDTree::kNearestNeighbour(const vector<int> &target, int k, vector<kDTreeNode *> &bestList) {
    // Implement k nearest neighbors search
    vector<kDTreeNode*> v;
    bestList = v;
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