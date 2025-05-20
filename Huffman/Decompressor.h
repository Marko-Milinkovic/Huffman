#pragma once
#include <string>
#include "HuffmanTree.h"

class Decompressor {
public:
    explicit Decompressor(const HuffmanTree& tree) : tree(&tree) {}
    std::string decompress(const std::string& binaryData);
    void decompress(const std::string& inputFile, const std::string& outputFile);

private:
    const HuffmanTree* tree; // Now properly initialized
};
