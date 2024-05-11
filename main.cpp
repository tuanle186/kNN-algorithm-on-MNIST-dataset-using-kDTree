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
    vector<int> point6({8, 1});
    vector<int> point7({9, 4});
    vector<int> point8({3, 5});

    myTree.insert(point1);
    myTree.insert(point2);
    myTree.insert(point3);
    myTree.insert(point4);
    myTree.insert(point5);
    myTree.insert(point6);
    myTree.insert(point7);
    myTree.insert(point8);
    myTree.preorderTraversal();
    cout << "end" << endl;
    myTree.inorderTraversal();
    cout << "end" << endl;
    myTree.postorderTraversal();
    cout << "end" << endl;
}

int main(int argc, const char *argv[])
{
    tc9();
    return 0;
}