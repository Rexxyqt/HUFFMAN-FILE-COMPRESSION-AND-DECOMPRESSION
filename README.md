# Huffman Algorithm: File Compression and Decompression

```text
██╗  ██╗██╗   ██╗███████╗███████╗███╗   ███╗ █████╗ ███╗   ██╗
██║  ██║██║   ██║██╔════╝██╔════╝████╗ ████║██╔══██╗████╗  ██║
███████║██║   ██║█████╗  █████╗  ██╔████╔██║███████║██╔██╗ ██║
██╔══██║██║   ██║██╔══╝  ██╔══╝  ██║╚██╔╝██║██╔══██║██║╚██╗██║
██║  ██║╚██████╔╝██║     ██║     ██║ ╚═╝ ██║██║  ██║██║ ╚████║
╚═╝  ╚═╝ ╚═════╝ ╚═╝     ╚═╝     ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝
```

A C++ implementation of Huffman's Algorithm for efficient file compression and decompression. This project was developed as a Data Structure and Algorithm project.

## FEATURES

- **Efficient Compression**: Uses Huffman coding to reduce file size.
- **Visual Frequency Table**: Displays character frequency, ASCII values, and Huffman codes during compression.
- **Binary Stream Preview**: Shows the formatted binary stream being generated.
- **Interactive CLI**: Easy-to-use menu with colored output and ASCII art.
- **Support for All Characters**: Processes standard and special characters (including newlines).

## HOW IT WORKS

1. **Frequency Analysis**: The program reads the input file and counts the frequency of each character.
2. **Huffman Tree Construction**: A priority queue-based greedy approach is used to build the Huffman Tree.
3. **Code Generation**: Unique prefix-free binary codes are assigned to each character based on their depth in the tree.
4. **Encoding/Decoding**: 
   - **Compression**: The file is rewritten using the generated binary codes, packed into bytes.
   - **Decompression**: The compressed file is read bit by bit and traversed through the Huffman Tree to recover original characters.

## GETTING STARTED

### Prerequisites
- A C++ compiler (G++, Clang, or MSVC).
- Windows OS (uses `<windows.h>` for console colors and UTF-8 support).

### COMPILATION
Run the following command in your terminal:
```bash
g++ -o HuffmanTool Huffman_Algorithm.cpp
```

### USAGE
1. Run the executable:
   ```bash
   ./HuffmanTool
   ```
2. Choose **[1] Compress File** and enter the filename (e.g., `MyFile.txt`).
3. Choose **[2] Decompress File** and enter the compressed filename.

## PROGRAMMERS/CREATOR
- **Rex Jemar B. Latayada**
- **Jhon Ryan S. Fullo**

*Date Finished: November 22, 2025*
