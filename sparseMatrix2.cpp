#include <iostream>

using namespace std;

class Node {
public:
    int row, col, value;
    Node* next;

    Node(int r, int c, int v) : row(r), col(c), value(v), next(nullptr) {}
};

class SparseMatrix {
private:
    int rows, cols;
    Node** matrix;

public:
    SparseMatrix(int r, int c) : rows(r), cols(c) {
        matrix = new Node*[rows];
        for (int i = 0; i < rows; ++i) {
            matrix[i] = nullptr;
        }
    }

    void addElement(int row, int col, int value) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            cout << "Invalid row or column index." << endl;
            return;
        }

        Node* newNode = new Node(row, col, value);
        newNode->next = matrix[row];
        matrix[row] = newNode;
    }

    int getElement(int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            cout << "Invalid row or column index." << endl;
            return 0;
        }

        Node* current = matrix[row];
        while (current) {
            if (current->col == col) {
                return current->value;
            }
            current = current->next;
        }
        return 0;  // Default value for non-existing elements
    }

    void display() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << getElement(i, j) << "\t";
            }
            cout << endl;
        }
    }
};

int main() {
    int rows, cols;
    cout << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the number of columns: ";
    cin >> cols;

    SparseMatrix matrix(rows, cols);

    int row, col, value;
    char another;

    do {
        cout << "Enter the row index (0 to " << rows - 1 << "): ";
        cin >> row;
        cout << "Enter the column index (0 to " << cols - 1 << "): ";
        cin >> col;
        cout << "Enter the value: ";
        cin >> value;

        matrix.addElement(row, col, value);

        cout << "Do you want to enter another element? (y/n): ";
        cin >> another;

    } while (another == 'y' || another == 'Y');

    cout << "\nSparse Matrix:" << endl;
    matrix.display();

    return 0;
}
