#pragma once
#include <iomanip>
#include <map>
#include "HuffmanTree.h"


class CompressionReport {
public:
    static void generateReport(const std::string& original,
        const std::string& compressed,
        const HuffmanTree& tree) {
        std::cout << "\n=== HUFFMAN COMPRESSION REPORT ===\n";

        // Basic file info
        printFileSizes(original, compressed);

        // Compression metrics
        printCompressionMetrics(original.size(), compressed.size());

        // Code table analysis
        printCodeTableAnalysis(tree.getCodeTable());

        // Byte frequency distribution
        printByteDistribution(original);
    }

private:
    static void printFileSizes(const std::string& original, const std::string& compressed) {
        std::cout << "\n[File Sizes]\n";
        std::cout << "Original:  " << original.size() << " bytes\n";
        std::cout << "Compressed: " << compressed.size() << " bytes\n";
        std::cout << "Overhead:  " << original.size() - compressed.size() << " bytes\n";
    }

    static void printCompressionMetrics(size_t original_size, size_t compressed_size) {
        double ratio = (1.0 - (double)compressed_size / original_size) * 100;
        double bits_per_symbol = (compressed_size * 8.0) / original_size;

        std::cout << "\n[Compression Metrics]\n";
        std::cout << "Compression Ratio: " << std::fixed << std::setprecision(2)
            << ratio << "%\n";
        std::cout << "Bits per Symbol: " << std::setprecision(3)
            << bits_per_symbol << " bits\n";
        std::cout << "Space Savings: " << (original_size - compressed_size)
            << " bytes saved\n";
    }


    static void printCodeTableAnalysis(const std::unordered_map<char, std::string>& codeTable) {
        std::cout << "\n[Code Table Analysis]\n";
        std::cout << std::left << std::setw(10) << "Symbol"
            << std::setw(15) << "Code"
            << "Length\n";

        for (const auto& pair : codeTable) {
            char symbol = pair.first;
            std::string code = pair.second;
            std::cout << std::setw(10) << (symbol == '\n' ? "\\n" : std::string(1, symbol))
                << std::setw(15) << code
                << code.length() << " bits\n";
        }
    }

    static void printByteDistribution(const std::string& original) {
        std::map<char, int> freqMap;
        for (char c : original) freqMap[c]++;

        std::cout << "\n[Byte Frequency Distribution]\n";
        std::cout << std::left << std::setw(10) << "Byte"
            << std::setw(15) << "Frequency"
            << "Percentage\n";

        for (const auto& pair : freqMap) {
            auto byte = pair.first;
            auto count = pair.second;
            double percentage = (count * 100.0) / original.size();
            std::cout << std::setw(10) << (byte == '\n' ? "\\n" : std::string(1, byte))
                << std::setw(15) << count
                << std::fixed << std::setprecision(2)
                << percentage << "%\n";
        }
    }
};
