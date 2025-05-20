#include "Compressor.h"
#include <fstream>

void Compressor::calculateFrequencies(const std::string& input) {
    frequencies.clear();
    for (char ch : input) {
        frequencies[ch]++;
    }
}

const std::unordered_map<char, size_t>& Compressor::getFrequencies() const {
    return frequencies;
}

std::string Compressor::compress(const std::string& input) {

    calculateFrequencies(input);
    tree.build(frequencies);

    std::string encoded;
    for (char ch : input) {
        encoded += tree.encode(std::string(1, ch));
    }
    return encoded;
}

void Compressor::compress(const std::string& inputFile, const std::string& outputFile)
{
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) throw std::runtime_error("Failed to open input file");

    std::string data((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    in.close();

    this->calculateFrequencies(data);
    this->tree.build(this->frequencies);

    std::string encoded = tree.encode(data);

    std::ofstream out(outputFile, std::ios::binary);
    if (!out) throw std::runtime_error("Failed to open output file");

    Node* root = this->tree.getRoot();
    tree.writeTree(out,root); // Serialize tree
    out.put('\n');       // Tree-data delimiter

    uint8_t currentByte = 0;
    int bitCount = 0;

    for (char bit : encoded) {
        currentByte = (currentByte << 1) | (bit - '0');
        bitCount++;

        if (bitCount == 8) {
            out.put(currentByte);
            bitCount = 0;
            currentByte = 0;
        }
    }

    if (bitCount > 0) {
        currentByte <<= (8 - bitCount);
        out.put(currentByte);
    }

    out.close();
}

