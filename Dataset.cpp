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