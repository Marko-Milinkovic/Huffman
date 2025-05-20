#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Compressor.h"
#include "Decompressor.h"
#include "CompresionReport.h"

std::string readFile(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) {
        throw std::runtime_error("Failed to open input file.");
    }

    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

void writeFile(const std::string& filename, const std::string& data) {
    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        throw std::runtime_error("Failed to open output file.");
    }

    out.write(data.data(), data.size());
}

void printCompressedFileBits(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) throw std::runtime_error("Cannot open compressed file");

    std::cout << "Compressed content (binary):\n";
    char byte;
    while (file.get(byte)) {
        for (int i = 7; i >= 0; --i) {
            std::cout << ((byte >> i) & 1);
        }
        std::cout << " ";
    }
    std::cout << "\n";
}

int main() {
    try {
        const std::string inputPath = "sample.txt";
        const std::string compressedPath = "compressed.huff";
        const std::string outputPath = "decompressed.txt";

        // Step 1: Read original file
        std::string original = readFile(inputPath);
        std::cout << "Original file loaded. Size: " << original.size() << " bytes\n";

        // Step 2: Compress it
        Compressor compressor;
        compressor.compress(inputPath, compressedPath);
        std::cout << "Compression completed. Output saved to '" << compressedPath << "'\n";
        //printCompressedFileBits(compressedPath);  // Binary format
        std::string compressed = readFile(compressedPath);
        //std::cout << "Compressed file size: " << compressed.size() << " bytes\n";
        
        // Step 3: Decompress it
        // Get reference to existing tree (no copy)
        const HuffmanTree& tree = compressor.getTree();
        //tree.writeTree(std::cout, tree.getRoot());

        Decompressor decompressor(tree);  // Now stores pointer to valid tree
        decompressor.decompress(compressedPath, outputPath);
        
        std::cout << "Decompression completed. Output saved to '" << outputPath << "'\n";
        std::string restored = readFile(outputPath);
        
        // Step 4: Verify correctness
        if (original.size() == restored.size()) {
            std::cout << "[] Success: Decompressed content matches original!\n";
            CompressionReport::generateReport(original, compressed, tree);
        }
        else {
            std::cout << "[] Error: Mismatch in decompressed output.\n";
        }
        
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

