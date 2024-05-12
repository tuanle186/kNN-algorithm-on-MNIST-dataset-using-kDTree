#include "main.hpp"
#include "Dataset.hpp"
/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */
struct kDTreeNode
{
    vector<int> data;
    kDTreeNode *left;
    kDTreeNode *right;
    kDTreeNode(vector<int> data, kDTreeNode *left = nullptr, kDTreeNode *right = nullptr)
    {
        this->data = data;
        this->left = left;
        this->right = right;
    }

    friend ostream &operator<<(ostream &os, const kDTreeNode &node)
    {
        os << "(";
        for (int i = 0; i < node.data.size(); i++)
        {
            os << node.data[i];
            if (i != node.data.size() - 1)
            {
                os << ", ";
            }
        }
        os << ")";
        return os;
    }
};

class kDTree
{
private:
    int k;
    kDTreeNode *root;

public:
    kDTree(int k = 2);
    ~kDTree();

    const kDTree &operator=(const kDTree &other);
    kDTree(const kDTree &other);
    kDTreeNode *cloneTree(const kDTreeNode *node);
    void clearTree(kDTreeNode *node);

    void inorderTraversal() const;
    void preorderTraversal() const;
    void postorderTraversal() const;
    int height() const;
    int nodeCount() const;
    int leafCount() const;

    void insert(const vector<int> &point);
    void remove(const vector<int> &point); 
    bool search(const vector<int> &point);
    void buildTree(const vector<vector<int>> &pointList);
    void nearestNeighbour(const vector<int> &target, kDTreeNode* &best);
    void kNearestNeighbour(const vector<int> &target, int k, vector<kDTreeNode *> &bestList);

private:
    void inorderTraversalHelper(kDTreeNode *node, bool& isFirst) const;
    void preorderTraversalHelper(kDTreeNode *node, bool& isFirst) const;
    void postorderTraversalHelper(kDTreeNode *node, bool& isFirst) const;
    int heightHelper(kDTreeNode *node) const;
    int nodeCountHelper(kDTreeNode *node) const;
    int leafCountHelper(kDTreeNode *node) const;
    kDTreeNode* insertHelper(kDTreeNode* node, const vector<int> &point, int depth);
    kDTreeNode* removeHelper(kDTreeNode* node, const vector<int> &point, int depth);
    kDTreeNode* findReplacementNode(kDTreeNode* node, int depth, int alpha);
    bool searchHelper(kDTreeNode* node, const vector<int> &point, int depth);
    kDTreeNode* buildTreeHelper(const vector<vector<int>> &points, int depth);
    void mergeSort(vector<vector<int>>& arr, int l, int r, int dim);
    void merge(vector<vector<int>>& arr, int l, int m, int r, int dim);
    void nearestNeighbourHelper(const vector<int>& target, kDTreeNode* node, int depth, kDTreeNode*& best);
    double distance(const vector<int>& a, const vector<int>& b);
    void kNearestNeighbourHelper(const vector<int>& target, int k, kDTreeNode* node, int depth, vector<pair<double, kDTreeNode*>>& nearestNeighbors);
};

class kNN
{
private:
    int k;
    Dataset *X_train;
    Dataset *y_train;
    int numClasses;

public:
    kNN(int k = 5);
    void fit(Dataset &X_train, Dataset &y_train);
    Dataset predict(Dataset &X_test);
    double score(const Dataset &y_test, const Dataset &y_pred);
};

// Please add more or modify as needed
