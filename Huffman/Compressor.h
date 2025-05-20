#pragma once
#include <string>
#include <unordered_map>
#include "HuffmanTree.h"

class Compressor {
public:
    std::string compress(const std::string& input);
    void compress(const std::string& inputFile, const std::string& outputFile);
    const std::unordered_map<char, size_t>& getFrequencies() const;

    const HuffmanTree& getTree() const { return tree; }

private:
    std::unordered_map<char, size_t> frequencies;
    HuffmanTree tree;

    void calculateFrequencies(const std::string& input);
};
