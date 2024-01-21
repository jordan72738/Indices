#include <iostream>
#include <vector>

using namespace std;

struct SparseMatrix {
    int rows, cols;
    vector<vector<int>> data;
};

void addElement(SparseMatrix &matrix, int row, int col, int value) {
    if (value != 0) {
        matrix.data.push_back({row, col, value});
    }
}

void display(const SparseMatrix &matrix) {
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j) {
            int element = 0;
            for (const auto &entry : matrix.data) {
                if (entry[0] == i && entry[1] == j) {
                    element = entry[2];
                    break;
                }
            }
            cout << element << " ";
        }
        cout << endl;
    }
}

int main() {
    SparseMatrix sparseMatrix;

    cout << "Enter number of rows and columns: ";
    cin >> sparseMatrix.rows >> sparseMatrix.cols;

    cout << "Enter non-zero elements (row col value), terminate with -1: " << endl;
    int row, col, value;

    while (true) {
        cin >> row;
        if (row == -1) break;

        cin >> col >> value;
        addElement(sparseMatrix, row, col, value);
    }

    cout << "Sparse Matrix:" << endl;
    display(sparseMatrix);

    return 0;
}
