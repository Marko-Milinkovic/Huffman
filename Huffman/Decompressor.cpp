#include "Decompressor.h"
#include <fstream>


std::string Decompressor::decompress(const std::string& binaryData) {
    return tree->decode(binaryData);
}

void Decompressor::decompress(const std::string& inputFile, const std::string& outputFile)
{   
    //std::cout << "aaaaaaaaaaaaaaaaaa";
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) throw std::runtime_error("Failed to open input file");

    this->tree->readTree(in); // Deserialize tree
    in.get(); // consume '\n'

    std::string bits;
    char byte;
    while (in.get(byte)) {
        for (int i = 7; i >= 0; --i) {
            bits += ((byte >> i) & 1) ? '1' : '0';
        }
    }

    std::string decoded = tree->decode(bits);

    std::ofstream out(outputFile, std::ios::binary);
    if (!out) throw std::runtime_error("Failed to open output file");
    out << decoded;
    out.close();
}

