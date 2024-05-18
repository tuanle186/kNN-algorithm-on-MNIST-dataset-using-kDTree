#include "kDTree.hpp"

/* -------------------------------------------------------------------------- */
/*                            kDTree Constructor                              */
/* -------------------------------------------------------------------------- */

kDTree::kDTree(int k) {
    this->k = k;
    this->root = nullptr;
}


/* -------------------------------------------------------------------------- */
/*                            kDTree Destructor                               */
/* -------------------------------------------------------------------------- */

kDTree::~kDTree() {
    clearTree(root);
}


/* -------------------------------------------------------------------------- */
/*                          Copy Assignment Operator                          */
/* -------------------------------------------------------------------------- */

const kDTree &kDTree::operator=(const kDTree &other) {
    if (this != &other) // Check for self-assignment
    {
        k = other.k;
        clearTree(root);
        root = cloneTree(other.root);
    }
    return *this;
}


/* -------------------------------------------------------------------------- */
/*                             Copy Constructor                               */
/* -------------------------------------------------------------------------- */

kDTree::kDTree(const kDTree &other) {
    k = other.k;
    root = cloneTree(other.root);
}


/* -------------------------------------------------------------------------- */
/*                               Clone Tree                                   */
/* -------------------------------------------------------------------------- */

kDTreeNode* kDTree::cloneTree(const kDTreeNode *node)
{
    if (node == nullptr)
        return nullptr;
    return new kDTreeNode(node->data, cloneTree(node->left), cloneTree(node->right));
}


/* -------------------------------------------------------------------------- */
/*                               Clear Tree                                   */
/* -------------------------------------------------------------------------- */

void kDTree::clearTree(kDTreeNode *node)
{
    if (node != nullptr)
    {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
}


/* -------------------------------------------------------------------------- */
/*                             Inorder Traversal                              */
/* -------------------------------------------------------------------------- */

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
            cout << ", ";
        }
    }
    cout << ")";
    
    inorderTraversalHelper(node->right, isFirst);
}

void kDTree::inorderTraversal() const {
    bool isFirst = true;
    inorderTraversalHelper(root, isFirst);
}


/* -------------------------------------------------------------------------- */
/*                             Preorder Traversal                             */
/* -------------------------------------------------------------------------- */

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
            cout << ", ";
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

/* -------------------------------------------------------------------------- */
/*                            Postorder Traversal                             */
/* -------------------------------------------------------------------------- */

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
            cout << ", ";
        }
    }
    cout << ")";
}

void kDTree::postorderTraversal() const {
    bool isFirst = true;
    postorderTraversalHelper(root, isFirst);
}

/* -------------------------------------------------------------------------- */
/*                                  Height                                    */
/* -------------------------------------------------------------------------- */

int kDTree::height() const {
    return heightHelper(root);
}

int kDTree::heightHelper(kDTreeNode *node) const {
    if (node == nullptr)
        return 0;
    return 1 + max(heightHelper(node->left), heightHelper(node->right));
}


/* -------------------------------------------------------------------------- */
/*                                Node Count                                  */
/* -------------------------------------------------------------------------- */

int kDTree::nodeCount() const {
    return nodeCountHelper(root);
}

int kDTree::nodeCountHelper(kDTreeNode *node) const {
    if (node == nullptr)
        return 0;
    return 1 + nodeCountHelper(node->left) + nodeCountHelper(node->right);
}


/* -------------------------------------------------------------------------- */
/*                                Leaf Count                                  */
/* -------------------------------------------------------------------------- */

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


/* -------------------------------------------------------------------------- */
/*                                 Insert                                     */
/* -------------------------------------------------------------------------- */

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


/* -------------------------------------------------------------------------- */
/*                                 Remove                                     */
/* -------------------------------------------------------------------------- */

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


/* -------------------------------------------------------------------------- */
/*                                 Search                                     */
/* -------------------------------------------------------------------------- */

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
 

/* -------------------------------------------------------------------------- */
/*                               Build Tree                                   */
/* -------------------------------------------------------------------------- */

void kDTree::merge_buildTree(vector<vector<int>>& arr, int l, int m, int r, int dim) {
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

void kDTree::mergeSort_buildTree(vector<vector<int>>& arr, int l, int r, int dim) {
    if (l >= r) {
        return;
    }
    int m = l + (r - l) / 2;
    mergeSort_buildTree(arr, l, m, dim);
    mergeSort_buildTree(arr, m + 1, r, dim);
    merge_buildTree(arr, l, m, r, dim);
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
    mergeSort_buildTree(const_cast<vector<vector<int>>&>(points), 0, points.size() - 1, dim);
    
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


/* -------------------------------------------------------------------------- */
/*                            Nearest Neighbour                               */
/* -------------------------------------------------------------------------- */

double kDTree::distance(const vector<int>& a, const vector<int>& b) {
    double dist = 0;
    for (int i = 0; i < k; ++i) {
        dist += pow(a[i] - b[i], 2);
    }
    return sqrt(dist);
}

void kDTree::nearestNeighbourHelper(const std::vector<int>& target, kDTreeNode* node, int depth, kDTreeNode*& best) {
    if (node == nullptr) {
        return;
    }

    // Determine dimension to compare
    int dim = depth % k;

    // Choose next node based on splitting plane
    kDTreeNode* nextNode = nullptr;
    if (target[dim] < node->data[dim]) {
        nextNode = node->left;
    } else {
        nextNode = node->right;
    }

    // Recursively search down the tree
    nearestNeighbourHelper(target, nextNode, depth + 1, best);

    // Calculate distance from target to current node
    double currentDist = distance(target, node->data);

    // Update best node if current node is closer or if it's the first node encountered
    if (best == nullptr || currentDist < distance(target, best->data)) {
        best = node;
    }

    // Check if there could be closer points on the other side of the splitting plane
    double splitDist = abs(target[dim] - node->data[dim]);
    if (splitDist <= distance(target, best->data)) {
        // Explore the other side of the tree from the current node
        nearestNeighbourHelper(target, (nextNode == node->left) ? node->right : node->left, depth + 1, best);
    }
}

void kDTree::nearestNeighbour(const std::vector<int>& target, kDTreeNode*& best) {
    best = nullptr;
    nearestNeighbourHelper(target, root, 0, best);
}


/* -------------------------------------------------------------------------- */
/*                           K Nearest Neighbour                              */
/* -------------------------------------------------------------------------- */

void kDTree::kNearestNeighbour(const vector<int>& target, int k, vector<kDTreeNode*>& bestList) {
    // Vector to store nearest neighbors sorted by distance
    vector<pair<double, kDTreeNode*>> nearestNeighbors;

    // Recursive helper function to perform k nearest neighbors search
    kNearestNeighbourHelper(target, k, root, 0, nearestNeighbors);

    // Extract k nearest neighbors from vector
    for (const auto& pair : nearestNeighbors) {
        bestList.push_back(pair.second);
    }
}

void kDTree::kNearestNeighbourHelper(const vector<int>& target, int k, kDTreeNode* node, int depth, vector<pair<double, kDTreeNode*>>& nearestNeighbors) {
    if (node == nullptr) {
        return;
    }

    // Determine dimension to compare
    int dim = depth % this->k;

    // Choose next node based on splitting plane
    kDTreeNode* nextNode = nullptr;
    if (target[dim] < node->data[dim]) {
        nextNode = node->left;
    } else {
        nextNode = node->right;
    }

    // Recursively search down the tree
    kNearestNeighbourHelper(target, k, nextNode, depth + 1, nearestNeighbors);

    // Calculate distance from target to current node
    double currentDist = distance(target, node->data);

    // Insert current node into vector
    nearestNeighbors.push_back({currentDist, node});

    // Sort vector based on distance
    mergeSort_kNearestNeighbour(nearestNeighbors, 0, nearestNeighbors.size() - 1);

    // Resize vector to maintain k nearest neighbors
    if (nearestNeighbors.size() > k) {
        nearestNeighbors.resize(k);
    }

    // Check if there could be closer points on the other side of the splitting plane
    double splitDist = std::abs(target[dim] - node->data[dim]);
    if (splitDist <= nearestNeighbors.back().first || nearestNeighbors.size() < k) {  // Use back() for largest distance
        // Explore the other side of the tree from the current node
        kDTreeNode* otherNode = (nextNode == node->left) ? node->right : node->left;
        kNearestNeighbourHelper(target, k, otherNode, depth + 1, nearestNeighbors);
    }
}

void kDTree::merge_kNearestNeighbour(vector<pair<double, kDTreeNode*>>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    vector<pair<double, kDTreeNode*>> leftArr(n1);
    vector<pair<double, kDTreeNode*>> rightArr(n2);

    // Copy data to temporary arrays
    for (int i = 0; i < n1; ++i) {
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        rightArr[j] = arr[mid + 1 + j];
    }

    // Merge the temporary arrays back into arr[left..right]
    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i].first <= rightArr[j].first) {
            arr[k] = leftArr[i];
            ++i;
        } else {
            arr[k] = rightArr[j];
            ++j;
        }
        ++k;
    }

    // Copy the remaining elements of leftArr, if any
    while (i < n1) {
        arr[k] = leftArr[i];
        ++i;
        ++k;
    }

    // Copy the remaining elements of rightArr, if any
    while (j < n2) {
        arr[k] = rightArr[j];
        ++j;
        ++k;
    }
}

void kDTree::mergeSort_kNearestNeighbour(vector<pair<double, kDTreeNode*>>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort_kNearestNeighbour(arr, left, mid);
        mergeSort_kNearestNeighbour(arr, mid + 1, right);

        // Merge the sorted halves
        merge_kNearestNeighbour(arr, left, mid, right);
    }
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
