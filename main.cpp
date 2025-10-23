// Nick Guevara
// CS 315
// 10/21/25
// Project 3


#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

#include "Scanner.hpp"
#include "utils.hpp"
#include "BinSearchTree.hpp"
#include "PriorityQueue.hpp"
#include "HuffmanTree.hpp"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    //create the paths
    std::string inputFileBaseName = baseNameWithoutTxt(argv[1]);

    fs::path dirPath = "input_output";
    fs::path inputFilePath = dirPath / argv[1];
    fs::path wordTokensPath = dirPath / (inputFileBaseName + ".tokens");
    fs::path freqFilePath = dirPath / (inputFileBaseName + ".freq");
    fs::path headerFilePath = dirPath / (inputFileBaseName + ".hdr");
    fs::path encodedFilePath = dirPath / (inputFileBaseName + ".code");

    // The next several if-statement make sure that the input file and directory exists
    // and that the output files are writeable.
    if (error_type status; (status = regularFileExistsAndIsAvailable(inputFilePath.string())) != NO_ERROR)
        exitOnError(status, inputFilePath.string());
    if (error_type status; (status = directoryExists(dirPath.string())) != NO_ERROR)
        exitOnError(status, dirPath.string());
    if (error_type status; (status = canOpenForWriting(wordTokensPath.string())) != NO_ERROR)
        exitOnError(status, wordTokensPath.string());
    if (error_type status; (status = canOpenForWriting(freqFilePath.string())) != NO_ERROR)
        exitOnError(status, freqFilePath.string());
    if (error_type status; (status = canOpenForWriting(headerFilePath.string())) != NO_ERROR)
        exitOnError(status, headerFilePath.string());
    if (error_type status; (status = canOpenForWriting(encodedFilePath.string())) != NO_ERROR)
        exitOnError(status, encodedFilePath.string());

    //part 1 : tokenization using Scanner, write .tokens
    
    std::vector<std::string> tokens;
    Scanner fileToWords(inputFilePath);

    if (error_type status; (status = fileToWords.tokenize(tokens)) != NO_ERROR)
        exitOnError(status, inputFilePath.string());

    if (error_type status; (status = writeVectorToFile(wordTokensPath.string(), tokens)) != NO_ERROR)
        exitOnError(status, wordTokensPath.string());

    // part 2 : build bst, output statistics, build priority queue, write .freq
    
    // Build BST
    BinSearchTree bst;
    bst.bulkInsert(tokens);
    std::vector<std::pair<std::string, int>> pairVector;
    bst.inorderCollect(pairVector);

    // Print BST statistics
    int minFreq = 0;
    int maxFreq = 0;
    if (!pairVector.empty()) {
        minFreq = pairVector.at(0).second;
        maxFreq = pairVector.at(0).second;
        for (std::size_t i = 1; i < pairVector.size(); ++i) {
            if (pairVector.at(i).second < minFreq) minFreq = pairVector.at(i).second;
            if (pairVector.at(i).second > maxFreq) maxFreq = pairVector.at(i).second;
        }
    }
    std::cout << "BST height: " << bst.height() << std::endl;
    std::cout << "BST unique words: " << bst.size() << std::endl;
    std::cout << "Total tokens: " << tokens.size() << std::endl;
    std::cout << "Min frequency: " << minFreq << std::endl;
    std::cout << "Max frequency: " << maxFreq << std::endl;
    
    //using the vector of word/frequency pairs from the BST, create a vector of TreeNodes and use them to build the priority queue
    std::vector<TreeNode*> treeNodes;
    for (std::size_t i = 0; i < pairVector.size(); i++) {
        treeNodes.push_back(new TreeNode(pairVector.at(i).first, pairVector.at(i).second));
    }
    PriorityQueue pq(treeNodes);

    //write frequencies to output.freq

    std::ofstream frequencyOutput(freqFilePath, std::ios::out | std::ios::trunc);
    pq.print(frequencyOutput);
    frequencyOutput.close();
    
    //delete the tree nodes created in treeNodes vector 
    for (std::size_t i = 0; i < treeNodes.size(); i++) {
        delete treeNodes.at(i);
    }

    //Part 3: Build the huffman tree, write the header, write the encoded file

    HuffmanTree ht = HuffmanTree::buildFromCounts(pairVector);

    std::ofstream headerOut(headerFilePath, std::ios::out | std::ios::trunc);
    if (error_type status; (status = ht.writeHeader(headerOut)) != NO_ERROR)
        exitOnError(status, headerFilePath.string());

    std::ofstream encodedOut(encodedFilePath, std::ios::out | std::ios::trunc);
    if (error_type status; (status = ht.encode(tokens, encodedOut, 80)) != NO_ERROR)
        exitOnError(status, encodedFilePath.string());
  


    return 0;
}