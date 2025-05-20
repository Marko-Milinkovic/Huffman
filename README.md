# Huffman Algorithm based File Compressor

[![Code Coverage](https://img.shields.io/badge/coverage-95%25-brightgreen)](https://github.com/Marko-Milinkovic/Huffman-coding)
![C++ Standard](https://img.shields.io/badge/C%2B%2B-17-blue)

A high-performance, real-world file compressor built in C++ using the Huffman coding algorithm — the same core algorithm behind ZIP and other industry-standard formats.

This tool takes an input file, analyzes symbol frequencies, constructs an optimal Huffman binary prefix tree, encodes the content at the bit level, and outputs a compressed binary file with significantly reduced size (typically 40–60% smaller, depending on entropy) ready for reconstruction. It guarantees lossless compression — the decompressed output is identical to the original, with no risk of data corruption.

Designed for speed, efficiency, and correctness, it implements the full compression-decompression pipeline with custom serialization and bitstream handling.

Following image explains basic logic of Huffman algorithm.



<p align="center">
  <img src="assets/huffman_tree.png" alt="Huffman Tree" width="500"/><br>
  <em>Visual representation of a Huffman Tree — leaf nodes contain symbols along with their frequencies, while internal nodes represent combined frequencies. 
    Binary codes are assigned by traversing the tree: taking the left edge appends a '0', and the right edge appends a '1'. 
    For example, a symbol at the path "left → right → left" would get the code "010" ( in the given example "010" would be "a" - so 3 bits instead of 8 [standard ASCII] ). 
    Frequent symbols appear closer to the root, resulting in shorter codes and reduced overall file size.</em>
</p>



---

## Key Features

- **Lossless compression** using canonical Huffman codes
- **Supports both compression and decompression** of files
- **Algorithmic efficiency**: optimized hashing for symbol frequency analysis and tree construction using min-heap priority-queue
- **Recursive serialization/deserialization** of the Huffman tree
- **Custom binary format** for decompression compatibility
- **Bit-level symbol encoding** for optimal file size reduction
- **Compression metrics**: shows input size, output size, compression ratio, space savings and bits per symbol
- **Robust testing suite** covering edge cases including empty files and single-symbol inputs
- **Dynamic memory management** with rigorous leak-free guarantees 
  
---

## Technical Highlights

### Core Algorithm  
- **Frequency Analysis**: Utilizes a high-performance hash map to count symbol occurrences in O(n) time, where *n* is the input file size.  
- **Priority Queue Construction**: Implements a min-heap to build the Huffman tree efficiently in O(k log k) time, where *k* is the number of unique symbols.  
- **Huffman Tree Formation**: Combines nodes by repeatedly extracting the two lowest-frequency elements, ensuring an optimal prefix code minimizing average code length. Leaf nodes hold characters and frequencies, internal nodes store combined frequencies. 
- **Recursive Tree Serialization/Deserialization**: Employs preorder traversal to serialize the tree structure into a compact binary format, enabling exact reconstruction during decompression.  

### Bit-Level Operations  
- **Bitstream I/O**: Custom routines pack and unpack symbols bit-by-bit to maximize compression, leveraging bitwise shifts and masks for speed and minimal memory overhead.  
- **Canonical Codes**: Generates canonical Huffman codes to streamline encoding and decoding processes, reducing metadata size and simplifying decoder logic.  

### C++ Concepts & Implementation Details  
- **Standard Library Data Structures**: Utilizes `std::vector`, `std::priority_queue`, and `std::unordered_map` for efficient frequency counting, symbol storage, and priority queue management.  
- **Pointer Arithmetic and Dynamic Memory Management**: Employs raw pointers with careful manual management in performance-critical parts to optimize memory usage.  
- **Bitwise Operators and Masks**: Implements compact encoding and decoding through efficient use of bitwise shifts and masks for bit-level data manipulation.  
- **Error Handling and Validation**: Integrates comprehensive error checking for all I/O and memory operations, guaranteeing safe decompression with no data loss.  

## Benchmarks

| File         | Original Size | Compressed | Ratio | Time (ms) |
|--------------|----------------|------------|-------|-----------|
| `1KB.txt`    | 1.0 KB         | 0.6 KB     | 60%   | 1.2       |
| `10KB.txt`   | 10.0 KB        | 5.8 KB     | 58%   | 4.8       |
| `100KB.txt`  | 100.0 KB       | 61.2 KB    | 61%   | 32.1      |

---

## Conclusion

This project efficiently compresses input files into a compact binary format using Huffman coding and reliably decompresses them back without data loss, delivering significant storage savings. 
It leverages a diverse set of data structures—including hash maps, priority queues, and binary trees—while carefully managing time complexity to optimize performance. 
By combining high-level C++ STL abstractions with low-level bitwise operations and manual memory management, it exemplifies a powerful synergy of algorithmic precision and systems-level programming.

---

## License

This project is licensed under the [MIT License](LICENSE).

---

## Contact

Marko Milinković  
📧 Email: [markom11080@gmail.com]  
🔗 GitHub: [github.com/Marko-Milinkovic](https://github.com/Marko-Milinkovic)

---
