#include "Dataset.hpp"

Dataset::Dataset() {
    nRows = 0;
    nCols = 0;
}

Dataset::~Dataset() {

}

bool Dataset::loadFromCSV(const char *fileName) {
    ifstream file(fileName);
    if (!file) {
        // cerr << "Error: Unable to open file " << fileName << endl;
        return false;
    }
    bool is1stRow = true;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string token;
        if (is1stRow) { // 1st row detected, add columns' names into colName
            while (getline(iss, token, ',')) {
                columnName.push_back(token);
                nCols++;
            }
            is1stRow = false;
        } else { // Not first Row
            list<int> newRow;
            while (getline(iss, token, ',')) {
                newRow.push_back(stoi(token));
            }
            data.push_back(newRow);
            nRows++;
        }
    }
    file.close();
    return true;
}

void Dataset::printHead(int nRows, int nCols) const {
    if (nRows < 0 || nCols <= 0) {
        return;
    }
    nRows = min(nRows, this->nRows);
    nCols = min(nCols, this->nCols);

    for (int i = 0; i < nCols; ++i) {
        if (i < nCols - 1) {
            cout << columnName[i] << " ";
        } else {
            cout << columnName[i];
        }
    }

    cout << endl;
    auto rowIt = data.begin();
    for (int i = 0; i < nRows; ++i, ++rowIt) {
        auto colIt = rowIt->begin();
        for (int j = 0; j < nCols; ++j, ++colIt) {
            cout << *colIt;
            if (j < nCols - 1) {
                cout << " ";
            }
        }
        if (i < nRows - 1) {
            cout << endl;
        }
    }
}

void Dataset::printTail(int nRows, int nCols) const {
    if (nRows < 0 || nCols <= 0) {
        return;
    }
    nRows = min(nRows, this->nRows);
    nCols = min(nCols, this->nCols);

    for (auto it = columnName.end() - nCols; it != columnName.end(); ++it) {
        cout << *it;
        if (it != columnName.end() - 1) {
            cout << " ";
        }
    }

    cout << endl;
    // Calculate the starting row for printing
    auto rowIt = data.begin();
    int startRow = this->nRows - nRows;
    advance(rowIt, startRow);

    // Print the subset of elements
    for (; rowIt != data.end(); ++rowIt) {
        // Calculate the starting column for printing
        auto colIt = rowIt->begin();
        int startCol = this->nCols - nCols;
        advance(colIt, startCol);

        // Print the elements
        for (int j = 0; colIt != rowIt->end(); ++colIt) {
            cout << *colIt;
            if (next(colIt) != rowIt->end()) {
                cout << " ";
            }
        }

        if (next(rowIt) != data.end()) {
            cout << endl;
        }
    }
}

void Dataset::getShape(int &nRows, int &nCols) const {
    nRows = this->nRows;
    nCols = this->nCols;
}

void Dataset::columns() const {
    for (auto it = columnName.begin(); it != columnName.end(); ++it) {
        cout << *it;
        if (it != columnName.end() - 1) {
            cout << " ";
        }
    }
}

bool Dataset::drop(int axis, int index, std::string columns) {
    if (axis != 0 && axis != 1) {
        cout << "axis is not 0 or 1" << endl;
        return false;
    }

    if (axis == 0) { // dropping a row
        if (index >= nRows || index < 0) {
            cout << "Index out of bound, fail to drop a col" << endl;
            return false;
        }
        auto rowIt = data.begin();
        advance(rowIt, index);
        data.erase(rowIt);
        nRows--;
        return true;
    } 
    else { // dropping a column
        // int colIndex = colName->getIndexOf(columns);
        int colIndex = 0;
        bool found = false;
        for (auto it = columnName.begin(); it < columnName.end(); ++it) {
            if (*it == columns) {
                found = true;
                break;
            }
            colIndex++;
        }

        if (!found) {
            cout << "Column's name not found, failed to drop a col" << endl;
            return false;
        }

        columnName.erase(columnName.begin() + colIndex);
        for (auto& row : data) {
            auto colIt = row.begin();
            advance(colIt, colIndex);
            row.erase(colIt);
        }
        nCols--;
        return true;
    }

    cout << "Failed to drop a row or a col" << endl;
    return false;
}

Dataset Dataset::extract(int startRow, int endRow, int startCol, int endCol) const {
    Dataset extractedDataset;
    // Preprocessing
    if (endRow == -1) { // takes all rows
        endRow = this->nRows - 1;
    }
    if (endCol == -1) { // takes all cols
        endCol = this->nCols - 1;
    }

    // Set the nRows and nCols attribute of extractedDataset
    extractedDataset.nRows = endRow - startRow + 1;
    extractedDataset.nCols = endCol - startCol + 1;

    if (extractedDataset.nRows < 0 || extractedDataset.nCols < 0) {
        throw std::out_of_range("get(): Out of range");
    }

    // Set the colName attribute of extractedDataset
    auto startColNameIt = columnName.begin() + startCol;
    auto endColNameIt = columnName.begin() + endCol + 1;
    for (auto it = startColNameIt; it != endColNameIt; ++it) {
        extractedDataset.columnName.push_back(*it);
    }

    // Set the data attribute of extractedDataset
    auto startRowIt = data.begin();
    auto endRowIt = data.begin();
    advance(startRowIt, startRow);
    advance(endRowIt, endRow + 1);

    list<list<int>> extractedData;
    for (auto rowIt = startRowIt; rowIt != endRowIt; ++rowIt) {
        auto startColIt = rowIt->begin();
        auto endColIt = rowIt->begin();
        advance(startColIt, startCol);
        advance(endColIt, endCol + 1);
        list<int> newExtractedRow;
        for (auto colIt = startColIt; colIt != endColIt; ++colIt) {
            newExtractedRow.push_back(*colIt);
        }
        extractedData.push_back(newExtractedRow);
    }
    extractedDataset.data = extractedData;
    return extractedDataset;
}

Dataset::Dataset(const Dataset &other) {
    this->nRows = other.nRows;
    this->nCols = other.nCols;
    this->columnName = other.columnName;
    this->data = other.data;
}

Dataset& Dataset::operator=(const Dataset& other) {
    if (this != &other) { // Check for self-assignment
        this->nRows = other.nRows;
        this->nCols = other.nCols;
        this->columnName = other.columnName;
        this->data = other.data;
    }
    return *this; // Return a reference to the modified object
}

void train_test_split(  Dataset& X,           // Input: features
                        Dataset& y,           // Input: labels
                        double test_size,     // Input: test_size (0, 1)
                        Dataset& X_train,     // Output
                        Dataset& X_test,      // Output
                        Dataset& y_train,     // Output
                        Dataset& y_test)      // Output
{
    // Preprocessing
    int nRows_original, nCols_original;
    X.getShape(nRows_original, nCols_original);
    int nRows_test = ceil(test_size*nRows_original);
    int nRows_train = nRows_original - nRows_test;

    // Extracting
    X_train = X.extract(0, nRows_train - 1, 0, -1);
    X_test = X.extract(nRows_train, -1, 0, -1);
    y_train = y.extract(0, nRows_train - 1, 0, -1);
    y_test = y.extract(nRows_train, -1, 0, -1);
}