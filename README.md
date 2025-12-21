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

## 🚀 Features

- **Efficient Compression**: Uses Huffman coding to reduce file size.
- **Visual Frequency Table**: Displays character frequency, ASCII values, and Huffman codes during compression.
- **Binary Stream Preview**: Shows the formatted binary stream being generated.
- **Interactive CLI**: Easy-to-use menu with colored output and ASCII art.
- **Support for All Characters**: Processes standard and special characters (including newlines).

## 🛠️ How it Works

1. **Frequency Analysis**: The program reads the input file and counts the frequency of each character.
2. **Huffman Tree Construction**: A priority queue-based greedy approach is used to build the Huffman Tree.
3. **Code Generation**: Unique prefix-free binary codes are assigned to each character based on their depth in the tree.
4. **Encoding/Decoding**: 
   - **Compression**: The file is rewritten using the generated binary codes, packed into bytes.
   - **Decompression**: The compressed file is read bit by bit and traversed through the Huffman Tree to recover original characters.

## 📂 Project Structure

- `Huffman_Algorithm.cpp`: Huffman class and logic.
- `MyFile.txt`: Sample text file for testing.

## 💻 Getting Started

### Prerequisites
- A C++ compiler (G++, Clang, or MSVC).
- Windows OS (uses `<windows.h>` for console colors and UTF-8 support).

### Compilation
Run the following command in your terminal:
```bash
g++ -o HuffmanTool Huffman_Algorithm.cpp
```

### Usage
1. Run the executable:
   ```bash
   ./HuffmanTool
   ```
2. Choose **[1] Compress File** and enter the filename (e.g., `MyFile.txt`).
3. Choose **[2] Decompress File** and enter the compressed filename.

## 👥 Authors
- **Rex Jemar B. Latayada**
- **Jhon Ryan S. Fullo**

*Date Finished: November 22, 2025*
