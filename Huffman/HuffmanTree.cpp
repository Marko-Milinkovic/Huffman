#include "HuffmanTree.h"
#include "CompareNode.h"
#include <stdexcept>

HuffmanTree::HuffmanTree() : root(nullptr) {}

HuffmanTree::~HuffmanTree()
{
	this->clear(root);
}

void HuffmanTree::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}


void HuffmanTree::build(const std::unordered_map<char, size_t>& frequencies) {
    // Priority queue using CompareNode
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> pq; // behaves as min heap, node with the smallest freq at the top
    // elements stored in the queue are pointers to Node objects
    // std::vector<Node*> underlaying container used to implement the heap
    // CompareNode defines ordering based on node frequency
    // built in priority_queue in C++ : first arg type of elements, second arg container, third arg priority logic

    for (const auto& pair : frequencies) {
        char ch = pair.first;
        size_t freq = pair.second;
        pq.push(new Node(ch, freq));
    }
    // each character is a separate node in the queue sorted by freq

    // take out two nodes with the smallest frequency
    // create a new parent node with left + right freq, symbol = '\0' initially
    // push the new merged block into the pq
    while (pq.size() > 1) {

        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* merged = new Node(left->frequency + right->frequency, left, right);
        pq.push(merged);
    }

    root = pq.top();
    buildCodeTable(root, "");
}

std::string HuffmanTree::encode(const std::string& text) const {
    std::string result;
    for (char ch : text) {
        auto it = codeTable.find(ch);
        if (it == codeTable.end()) {
            throw std::runtime_error(std::string("Character not in code table: ") + ch);
        }
        result += it->second;
    }
    return result;
}

std::string HuffmanTree::decode(const std::string& binaryString) const {
    std::string result;
    Node* current = root;

    for (char bit : binaryString) {
        if (!current) {
            throw std::runtime_error("Invalid Huffman tree or binary string.");
        }

        if (bit == '0') {
            current = current->left;
        }
        else if (bit == '1') {
            current = current->right;
        }
        else {
            throw std::runtime_error("Invalid character in binary string. Only '0' and '1' allowed.");
        }

        if (current->isLeaf()) {
            result += current->symbol;
            current = root; // restart from root for next symbol
        }
    }

    return result;
}


void HuffmanTree::buildCodeTable(Node* node, const std::string& path) {
    // map each character to its binary string code
    if (!node) return;

    // accumulated path so far is the Huffman code for that symbol 
    if (node->isLeaf()) {
        codeTable[node->symbol] = path;
        return;
    }

    // if you go left add 0, if you go right add 1
    buildCodeTable(node->left, path + "0");
    buildCodeTable(node->right, path + "1");
}

std::unordered_map<char, std::string> HuffmanTree::getCodeTable() const {
    return codeTable;
}

void HuffmanTree::writeTree(std::ostream& out, Node* node) const
{
    if (!node) return;

    if (node->isLeaf()) {
        out.put('L');               // Indicate leaf node
        out.put(node->symbol);     // Write character
    }
    else {
        out.put('I');              // Indicate internal node
        writeTree(out, node->left);
        writeTree(out, node->right);
    }
}

Node* HuffmanTree::readTree(std::istream& in) const
{
    char type = in.get();
    if (type == 'L') {
        char symbol = in.get();
        return new Node(symbol, 0); // Frequency doesn't matter here
    }
    else if (type == 'I') {
        Node* left = readTree(in);
        Node* right = readTree(in);
        return new Node(0, left, right);
    }
    return nullptr; // For safety (e.g. corrupt input)
}

