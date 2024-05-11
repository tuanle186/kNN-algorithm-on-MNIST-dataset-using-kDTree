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

int main(int argc, const char *argv[])
{
    tc3();
    return 0;
}