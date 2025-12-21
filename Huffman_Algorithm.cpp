//DATA STRUCTURE AND ALGORITHM - PROJECT#2: FILE COMPRESSION AND DECOMPRESSION USING HUFFMAN'S ALGORITHM
/*PROGRAMMERS:
    - Latayada, Rex Jemar B.
    - Fullo, Jhon Ryan S.
 *DATE STARTED:
    - November 1, 2025
 *DATE FINISHED:
    - November 22, 2025
*/

//Rex
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>
#define MAXCHARACTER 256
using namespace std;

struct Node {
    char character;
    int count;
    Node* left;
    Node* right;

    Node(int c) {
        count = c;
        left = nullptr;
        right = nullptr;
    }

    Node(char ch, int c) {
        character = ch;
        count = c;
        left = nullptr;
        right = nullptr;
    }
};

struct NodePQ {
    char ch;
    int freq;
    NodePQ* Left;
    NodePQ* Right;
    NodePQ* next;

    NodePQ(char c, int f) {
        ch = c;
        freq = f;
        Left = nullptr;
        Right = nullptr;
        next = nullptr;
    }
};

struct PriorityQueuePQ {
    NodePQ* front;
    NodePQ* rear;

    PriorityQueuePQ() {
        front = nullptr;
        rear = nullptr;
    }

    bool isempty() {
        return front == nullptr;
    }

    void enqueue(NodePQ* x) {
        if (front == nullptr) {
            front = x;
            rear = x;
            return;
        }

        NodePQ* p = front;
        NodePQ* q = nullptr;

        while (p != nullptr && x->freq >= p->freq) {
            q = p;
            p = p->next;
        }

        if (p == front) {
            x->next = front;
            front = x;
        }
        else if (q == rear) {
            rear->next = x;
            rear = x;
        }
        else {
            q->next = x;
            x->next = p;
        }
    }

    NodePQ* dequeue() {
        if (front == nullptr) {
            return nullptr;
        }

        NodePQ* temp = front;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        temp->next = nullptr;
        return temp;
    }
};

class Huffman {
private:
    string HuffmanCode[MAXCHARACTER];
    char charlist[MAXCHARACTER];
    int charCount;
    int freqList[MAXCHARACTER];
    string lastParsedFileName;
    NodePQ* buildHuffmanTree(PriorityQueuePQ& pq);
    void generateCodesPQ(NodePQ* root, string code);

public:
    Huffman();
    int getFileSize(string filename);
    void countFreq(string filename, int filesize);
    void decompress(string inputFile, string outputFile = "");
    void buildTreeAndCodes();
    void printDebugTable();
    void compress(string inputFile, string outputFile = "");
    string generateOutputFilename(string inputFile, bool decompress);
};

void Color(int color);

//Ryan
NodePQ* Huffman::buildHuffmanTree(PriorityQueuePQ& pq) {
    while (!pq.isempty() && pq.front->next != nullptr) {
        NodePQ* left = pq.dequeue();
        NodePQ* right = pq.dequeue();
        NodePQ* parent = new NodePQ('\0', left->freq + right->freq);
        parent->Left = left;
        parent->Right = right;
        pq.enqueue(parent);
    }
    return pq.dequeue();
}

//Ryan
void Huffman::generateCodesPQ(NodePQ* root, string code) {
    if (!root)
        return;

    if (!root->Left && !root->Right) {
        HuffmanCode[(unsigned char)root->ch] = code;
        return;
    }

    generateCodesPQ(root->Left, code + "0");
    generateCodesPQ(root->Right, code + "1");
}

//Ryan
void Huffman::buildTreeAndCodes() {
    PriorityQueuePQ pq;
    for (int i = 0; i < charCount; i++) {
        pq.enqueue(new NodePQ(charlist[i], freqList[i]));
    }
    NodePQ* rootPQ = buildHuffmanTree(pq);
    generateCodesPQ(rootPQ, "");
}

//Ryan
Huffman::Huffman() {
    charCount = 0;
    for (int i = 0; i < MAXCHARACTER; i++) {
        HuffmanCode[i] = "";
    }
}

//Ryan
int Huffman::getFileSize(string filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        return 0;
    }

    int size = 0;
    char ch;
    while (file.get(ch)) {
        size++;
    }

    file.close();
    return size;
}

//Ryan
void Huffman::countFreq(string filename, int filesize) {
    lastParsedFileName = filename;
    ifstream file(filename, ios::binary);
    if (!file) {
        cout << "File Error\n";
        return;
    }

    bool used[256] = { false };
    charCount = 0;

    for (int i = 0; i < filesize; i++) {
        char ch;
        file.get(ch);
        if (!used[(unsigned char)ch]) {
            used[(unsigned char)ch] = true;
            charlist[charCount] = ch;
            freqList[charCount] = 0;
            charCount++;
        }
    }

    file.clear();
    file.seekg(0, ios::beg);

    for (int i = 0; i < filesize; i++) {
        char ch;
        file.get(ch);
        for (int j = 0; j < charCount; j++) {
            if (ch == charlist[j])
                freqList[j]++;
        }
    }

    file.close();
}

//Ryan
void Huffman::decompress(string inputFile, string outputFile) {
    if (outputFile.empty()) {
        outputFile = generateOutputFilename(inputFile, true);
    }

    ifstream in(inputFile, ios::binary);
    if (!in) {
        cout << "File not found.\n";
        return;
    }

    char c;
    in.get(c);
    int readCharCount = (unsigned char)c;

    char fileCharList[MAXCHARACTER];
    int fileFreqList[MAXCHARACTER];

    for (int i = 0; i < readCharCount; i++) {
        in.get(fileCharList[i]);
        in.read((char*)&fileFreqList[i], sizeof(int));
    }

    charCount = readCharCount;

    for (int i = 0; i < charCount; i++) {
        charlist[i] = fileCharList[i];
        freqList[i] = fileFreqList[i];
    }

    buildTreeAndCodes();

    int totalBits = 0;
    in.read((char*)&totalBits, sizeof(int));

    ofstream out(outputFile, ios::binary);
    if (!out) {
        cout << "Error creating output file.\n";
        return;
    }

    PriorityQueuePQ pq;
    for (int i = 0; i < charCount; i++) {
        NodePQ* node = new NodePQ(charlist[i], freqList[i]);
        pq.enqueue(node);
    }

    NodePQ* rootPQ = buildHuffmanTree(pq);
    NodePQ* current = rootPQ;

    int bitsRead = 0;
    char byte;

    while (in.get(byte) && bitsRead < totalBits) {
        for (int bitIndex = 7; bitIndex >= 0 && bitsRead < totalBits; bitIndex--) {
            int bit = ((byte >> bitIndex) & 1);
            current = (bit == 0) ? current->Left : current->Right;

            if (!current->Left && !current->Right) {
                out.put(current->ch);
                current = rootPQ;
            }

            bitsRead++;
        }
    }

    in.close();
    out.close();
    Color(7);
    int decompressedSize = getFileSize(outputFile);
    cout << "Decompressed file size: " << decompressedSize << " bytes\n";
    cout << "Decompression Done!\n";
    system("pause");
}

//Rex
void Huffman::printDebugTable() {
    cout << left << setw(20) << "CHARACTER" << setw(20) << "ASCII" << setw(20) << "FREQUENCY" << setw(20) << "HUFFMAN CODE" <<endl;
    cout << "=========================================================================\n";

    for (int i = 0; i < charCount; i++) {
        string displayChar = (charlist[i] == '\n') ? "\\n" : string(1, charlist[i]);
        cout << setw(20) << displayChar;
        cout << setw(20) << int((unsigned char)charlist[i]);
        cout << setw(20) << freqList[i];
        cout << setw(20) << HuffmanCode[(unsigned char)charlist[i]] << "\n";
    }

    cout << "=========================================================================\n";
    cout << "Binary stream: ";
    string combinedBits = "";

    ifstream file(lastParsedFileName, ios::binary);
    if (!file) {
        cout << "cannot open.\n";
        return;
    }

    char ch;
    while (file.get(ch)) {
        combinedBits += HuffmanCode[(unsigned char)ch];
    }
    file.close();

    int bitCount = combinedBits.size();
    int padding = (8 - (bitCount % 8)) % 8;

    for (int i = 0; i < padding; i++) {
        combinedBits += '0';
    }

    for (int i = 0; i < combinedBits.size(); i++) {
        cout << combinedBits[i];
        if ((i + 1) % 8 == 0) cout << "  ";
    }

    cout << "\n=========================================================================\n";
}

//Rex
string Huffman::generateOutputFilename(string inputFile, bool decompress) {
    string base = inputFile;
    string output;
    int counter = 1;

    int dotPos = -1;
    for (int i = base.length() - 1; i >= 0; i--) {
        if (base[i] == '.') {
            dotPos = i;
            break;
        }
    }
    if (dotPos != -1) {
        base = base.substr(0, dotPos);
    }

    if (!decompress) {
        output = base + "_compressed.txt";
        while (true) {
            ifstream check(output);
            if (!check) break;
            check.close();
            output = base + "_compressed(" + to_string(counter++) + ").txt";
        }
    } else {
        int suffixPos = -1;
        for (int i = base.length() - 1; i >= 0; i--) {
            if (i >= 10) {
                if (base.substr(i - 10, 10) == "_compressed") {
                    suffixPos = i - 10;
                    break;
                }
            }
        }
        if (suffixPos != -1) {
            base = base.substr(0, suffixPos);
        }

        output = base + "_decompressed.txt";
        while (true) {
            ifstream check(output);
            if (!check) break;
            check.close();
            output = base + "_decompressed(" + to_string(counter++) + ").txt";
        }
    }

    return output;
}

//Rex
void Huffman::compress(string inputFile, string outputFile) {
    Color(15);
    if (outputFile.empty()) {
        outputFile = generateOutputFilename(inputFile, false);
    }

    int filesize = getFileSize(inputFile);
    if (filesize == 0) {
        cout << "File error\n";
        return;
    }
    cout << "Original file size: " << filesize << " bytes\n";

    countFreq(inputFile, filesize);
    buildTreeAndCodes();

    ofstream out(outputFile, ios::binary);
    ifstream in(inputFile, ios::binary);
    ofstream debug("debug_" + outputFile);

    if (!out || !in || !debug) {
        cout << "Error opening files.\n";
        return;
    }
    cout <<"\n";
    printDebugTable();

    out.put((char)charCount);
    for (int i = 0; i < charCount; i++) {
        out.put(charlist[i]);
        out.write((char*)&freqList[i], sizeof(int));
    }

    int totalBits = 0;
    char ch;
    while (in.get(ch)) {
        totalBits += HuffmanCode[(unsigned char)ch].size();
    }

    in.clear();
    in.seekg(0, ios::beg);
    out.write((char*)&totalBits, sizeof(int));

    char buffer = 0;
    int count = 0;
    
    debug << charCount << " ";
    for (int i = 0; i < charCount; i++) {
        debug << charlist[i] << freqList[i] << " ";
    }
    debug << totalBits << endl;  
    
    while (in.get(ch)) {
        string code = HuffmanCode[(unsigned char)ch];
        for (char bit : code) {
            buffer <<= 1;
            if (bit == '1') buffer |= 1;
            count++;
            if (count == 8) {
                out.put(buffer);
                debug.put(buffer);  
                buffer = 0;
                count = 0;
            }
        }
    }

    if (count > 0) {
        buffer <<= (8 - count);
        out.put(buffer);
        debug.put(buffer);
    }

    in.close();
    out.close();
    debug.close();

    int compressedSize = getFileSize(outputFile);
    cout << "Compressed file size: " << compressedSize << " bytes\n";
    cout << "Compression Done! Output: " << outputFile << endl;
    system("pause");
}
//Rex
void Color(int color) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, color);
}

//Rex
int main() {
    SetConsoleOutputCP(CP_UTF8);
    Huffman h;
    int choice;
    string inFile;

    while (true) {
    Color(6);
    system("cls");
    cout << "██╗  ██╗██╗   ██╗███████╗███████╗███╗   ███╗ █████╗ ███╗   ██╗\n"
         << "██║  ██║██║   ██║██╔════╝██╔════╝████╗ ████║██╔══██╗████╗  ██║\n"
         << "███████║██║   ██║█████╗  █████╗  ██╔████╔██║███████║██╔██╗ ██║\n"
         << "██╔══██║██║   ██║██╔══╝  ██╔══╝  ██║╚██╔╝██║██╔══██║██║╚██╗██║\n"
         << "██║  ██║╚██████╔╝██║     ██║     ██║ ╚═╝ ██║██║  ██║██║ ╚████║\n"
         << "╚═╝  ╚═╝ ╚═════╝ ╚═╝     ╚═╝     ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝\n";
         Color(11);
        cout << "[1] Compress File\n[2] Decompress File\n[3] Exit\nChoice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            system("cls");
            Color(10);
            cout << "=====COMPRESS FILE=====" <<endl;
            cout << "Input file: ";
            Color(7);
            cin >> inFile;
            Color(11);
            cout << "Loading:| ";
            for(int i = 0; i < 50; i++) {
                Color(6);
                cout <<"█";
                Sleep(10);
            }
            Color(11);
            cout << " | [FINISHED]\n";
            h.compress(inFile);
        } else if (choice == 2) {
            system("cls");
            Color(10);
            cout << "=====DECOMPRESS FILE=====" <<endl;
            cout << "Compressed file: ";
            Color(7);
            cin >> inFile;
            Color(11);
            cout << "Loading:| ";
            for(int i = 0; i < 50; i++) {
                Color(6);
                cout <<"█";
                Sleep(10);
            }
            Color(11);
            cout << " | [FINISHED]\n";
            h.decompress(inFile);
        } else if (choice == 3) {
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
