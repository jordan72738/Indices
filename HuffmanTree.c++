#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// A Huffman tree node
struct Node {
    char data;
    unsigned freq;
    Node *left, *right;

    Node(char data, unsigned freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

// For comparison of two heap nodes (needed in min heap)
struct compare {
    bool operator()(Node* l, Node* r) {
        return (l->freq > r->freq);
    }
};

// Utility function to print Huffman codes
void printCodes(Node* root, string str) {
    if (!root) return;

    if (root->data != '$') cout << str << " ";

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

// The main function that builds a Huffman Tree and print codes by traversing the tree
void buildHuffmanTree(vector<char>& data, vector<int>& freq, int size) {
    Node *left, *right, *top;

    // Create a min heap & insert all characters of data[]
    priority_queue<Node*, vector<Node*>, compare> minHeap;

    for (int i = 0; i < size; ++i)
        minHeap.push(new Node(data[i], freq[i]));

    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1) {
        // Extract the two minimum freq items from min heap
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with frequency equal to the sum of the two nodes frequencies.
        // '$' is a special value for internal nodes, not used
        top = new Node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        minHeap.push(top);
    }

    // Print Huffman codes using the Huffman tree built above
    printCodes(minHeap.top(), "");
}

int main() {
    string input;
    cout << "Enter a string: ";
    cin >> input;

    vector<char> data;
    vector<int> freq;
    int frequency;

    for (char ch : input) {
        cout << "Enter the frequency for " << ch << ": ";
        cin >> frequency;
        data.push_back(ch);
        freq.push_back(frequency);
    }

    buildHuffmanTree(data, freq, data.size());

    return 0;
}
