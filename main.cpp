#include "kDTree.hpp"

// void tc1()
// {
//     Dataset dataset;
//     dataset.loadFromCSV("mnist.csv");
//     dataset.printHead(10, 10);
//     std::cout << endl;
//     dataset.printTail(10, 10);
//     std::cout << endl;
//     int nRows, nCols;
//     dataset.getShape(nRows, nCols);
//     std::cout << "Shape: " << nRows << "x" << nCols << endl;
// }

// void tc2()
// {
//     Dataset dataset;
//     dataset.loadFromCSV("mnist.csv");
//     int nRows, nCols;

//     Dataset feature = dataset.extract(0, -1, 1, -1);
//     Dataset label = dataset.extract(0, -1, 0, 0);
//     feature.getShape(nRows, nCols);
//     std::cout << "Feature shape: " << nRows << "x" << nCols << endl;
//     label.getShape(nRows, nCols);
//     std::cout << "Label shape: " << nRows << "x" << nCols << endl;
// }

void tc3()
{
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    int nRows, nCols;

    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);

    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    X_train.getShape(nRows, nCols);
    std::cout << "X_train shape: " << nRows << "x" << nCols << endl;
    X_test.getShape(nRows, nCols);
    std::cout << "X_test shape: " << nRows << "x" << nCols << endl;
    y_train.getShape(nRows, nCols);
    std::cout << "y_train shape: " << nRows << "x" << nCols << endl;
    y_test.getShape(nRows, nCols);
    std::cout << "y_test shape: " << nRows << "x" << nCols << endl;
}

// void tc4()
// {
//     Dataset dataset;
//     dataset.loadFromCSV("mnist.csv");
//     int nRows, nCols;

//     kNN knn;
//     Dataset X_train, X_test, y_train, y_test;
//     Dataset feature = dataset.extract(0, -1, 1, -1);
//     Dataset label = dataset.extract(0, -1, 0, 0);

//     train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
//     knn.fit(X_train, y_train);
//     Dataset y_pred = knn.predict(X_test);

//     std::cout << "y_pred" << endl;
//     y_pred.printHead(10, 10);
//     std::cout << endl;
//     std::cout << "y_test" << endl;
//     y_test.printHead(10, 10);
//     std::cout << endl;
// }

// void tc5()
// {

//     Dataset dataset;
//     dataset.loadFromCSV("mnist.csv");
//     int nRows, nCols;

//     kNN knn;
//     Dataset X_train, X_test, y_train, y_test;
//     Dataset feature = dataset.extract(0, -1, 1, -1);
//     Dataset label = dataset.extract(0, -1, 0, 0);

//     train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
//     knn.fit(X_train, y_train);
//     Dataset y_pred = knn.predict(X_test);
//     double accuracy = knn.score(y_test, y_pred);
//     std::cout << "Accuracy: " << accuracy << endl;
// }


void tc6() {
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    dataset.printHead(5, 10);
    int nRows, nCols;
    dataset.getShape(nRows, nCols);
    cout << "Shape: " << nRows << "x" << nCols << endl;
    dataset.drop(1, 0, "1x1");
    dataset.printHead(5, 10);
    dataset.getShape(nRows, nCols);
    cout << "Shape: " << nRows << "x" << nCols << endl;
}

void tc7() {
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    dataset.printHead(15, 15);
    cout << endl;
    Dataset extractedDataset = dataset.extract(2, 10, 4, 10);

    extractedDataset.printHead(10000, 10000);
}

void tc8() {
    Dataset dataset1;
    dataset1.loadFromCSV("mnist.csv");
    dataset1.printHead();

    Dataset dataset2 = dataset1;
    dataset2.printHead();
}

void tc9() {
    // (5, 6), (2, 2), (7, 3), (2, 8), (8, 7), (8, 1), (9, 4), (3, 5)
    kDTree myTree;
    vector<int> point1({5, 6});
    vector<int> point2({2, 2});
    vector<int> point3({7, 3});
    vector<int> point4({2, 8});
    vector<int> point5({8, 7});
    vector<int> point6({8, 2});
    vector<int> point7({9, 5});
    vector<int> point8({3, 5});
    vector<int> point9({9, 2});

    myTree.insert(point1);
    myTree.insert(point2);
    myTree.insert(point3);
    myTree.insert(point4);
    myTree.insert(point5);
    myTree.insert(point6);
    myTree.insert(point7);
    myTree.insert(point8);
    myTree.insert(point9);

    // myTree.remove(point1);

    cout << "preOrder: ";
    myTree.preorderTraversal();
    cout << "end" << endl;
    cout << "inOrder: ";
    myTree.inorderTraversal();
    cout << "end" << endl;
    cout << "postOrder:";
    myTree.postorderTraversal();
    cout << "end" << endl;

    cout << "Height: " << myTree.height() << endl;
    cout << "Node count: " << myTree.nodeCount() << endl;
    cout << "Left count: " << myTree.leafCount() << endl;

    cout << "Search (9, 2): " << myTree.search(point9) << endl;
    vector<int> target({9, 3});
    kDTreeNode* best;
    myTree.nearestNeighbour(target, best);
    cout << "Nearest Neighbour: (" << best->data[0] << ", " << best->data[1] << ")" << endl;
}

void tc10() {
    vector<int> p1({5, 6});
    vector<int> p2({2, 2});
    vector<int> p3({7, 3});
    vector<int> p4({2, 8});
    vector<int> p5({8, 7});
    vector<int> p6({8, 1});
    vector<int> p7({9, 4});
    vector<int> p8({3, 5});
    vector<vector<int>> points({p1, p2, p3, p4, p5, p6, p7, p8});
    kDTree myTree;
    myTree.buildTree(points);
    cout << "preOrder: ";
    myTree.preorderTraversal();
    cout << "end" << endl;
    cout << "inOrder: ";
    myTree.inorderTraversal();
    cout << "end" << endl;
    cout << "postOrder:";
    myTree.postorderTraversal();
    cout << "end" << endl;
    cout << "Height: " << myTree.height() << endl;
    cout << "Node count: " << myTree.nodeCount() << endl;
    cout << "Leaf count: " << myTree.leafCount() << endl;
}

void tc11() {
    vector<int> p1({1, 1});
    vector<int> p2({2, 2});
    vector<int> p3({3, 3});
    vector<int> p4({3, 3});
    vector<int> p5({4, 4});
    vector<int> p6({5, 5});
    vector<int> p7({6, 6});
    vector<int> p8({7, 7});

    vector<vector<int>> points({p1, p2, p3, p4, p5, p6, p7, p8});
    kDTree myTree;
    myTree.buildTree(points);
    cout << "preOrder: ";
    myTree.preorderTraversal();
    cout << "end" << endl;
    cout << "inOrder: ";
    myTree.inorderTraversal();
    cout << "end" << endl;
    cout << "postOrder:";
    myTree.postorderTraversal();
    cout << "end" << endl;
    cout << "Height: " << myTree.height() << endl;
    cout << "Node count: " << myTree.nodeCount() << endl;
    cout << "Leaf count: " << myTree.leafCount() << endl;
}

int main(int argc, const char *argv[])
{
    tc9();
    return 0;
}