#pragma once
#include "Node.h"
#include <unordered_map>
#include <string>
#include <queue>
#include <iostream>

class HuffmanTree {
public:

    HuffmanTree();  // default constructor
    ~HuffmanTree(); // destructor

    void build(const std::unordered_map<char, size_t>& frequencies); // char and it's frequency map
    std::string encode(const std::string& text) const;
    std::string decode(const std::string& binaryString) const;
    std::unordered_map<char, std::string> getCodeTable() const;

    void writeTree(std::ostream& out, Node* node) const;
    Node* readTree(std::istream& in) const;

    Node* getRoot() const { return this->root; }

private:
    Node* root;
    std::unordered_map<char, std::string> codeTable;

    void buildCodeTable(Node* node, const std::string& path);
    void clear(Node* node);  // cleanup helper
};

