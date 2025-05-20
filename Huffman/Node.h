#pragma once

class Node {
public:

    char symbol;            // Valid only for leaf nodes
    size_t frequency;       // Frequency of symbol(s) in the subtree
    Node* left;             // Left child
    Node* right;            // Right child

    Node(char symbol, size_t frequency);
    Node(size_t frequency, Node* left, Node* right);
    bool isLeaf() const;
    ~Node();

};
