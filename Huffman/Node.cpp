#include "Node.h"

Node::Node(char symbol, size_t frequency)
    : symbol(symbol), frequency(frequency), left(nullptr), right(nullptr) {}

Node::Node(size_t frequency, Node* left, Node* right)
    : symbol('\0'), frequency(frequency), left(left), right(right) {}

bool Node::isLeaf() const {
    return left == nullptr && right == nullptr;
}

Node::~Node() {
    
}
