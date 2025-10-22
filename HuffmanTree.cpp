#include "HuffmanTree.hpp"
#include "PriorityQueue.hpp"
#include <map>

HuffmanTree HuffmanTree::buildFromCounts(const std::vector<std::pair<std::string, int>>& counts) {

    if (counts.empty()) {
        HuffmanTree emptyTree;
        return emptyTree;
    }

    //Convert each pair to a node
    std::vector<TreeNode*> TreeNodes;
    for (std::size_t i = 0; i < counts.size(); i++) {
        TreeNodes.push_back(new TreeNode(counts.at(i).first, counts.at(i).second));
    }

    //Create a PriorityQueue containing the nodes
    PriorityQueue queue(TreeNodes);

    if (queue.size() == 1) {
        HuffmanTree singleTree;
        singleTree.root_ = queue.extractMin();
        return singleTree;
    }

    //Build the tree's internal nodes
    while (queue.size() > 1) {
        TreeNode* left = queue.extractMin();
        TreeNode* right = queue.extractMin();
        if (right->getWord() < left->getWord()) {
            TreeNode* temp = left;
            left = right;
            right = temp;
        }
        const int internalNodeFrequency = left->getFrequency() + right->getFrequency();
        std::string internalNodeWord;
        if (left->getWord() < right->getWord()) {
            internalNodeWord = left->getWord();
        }
        else {
            internalNodeWord = right->getWord();
        }


        TreeNode* internalNode = new TreeNode(internalNodeWord, internalNodeFrequency);
        internalNode->setLeft(left);
        internalNode->setRight(right);
        queue.insert(internalNode);
    }

    TreeNode* rootPointer;
    if (queue.empty()) {
        rootPointer = nullptr;
    }
    else {
        rootPointer = queue.extractMin();
    }

    HuffmanTree result;
    result.root_ = rootPointer;
    return result;
}

// deletes the entire Huffman tree
HuffmanTree::~HuffmanTree() {
    destroy(root_);
    root_ = nullptr;
}                         

// Build a vector of (word, code) pairs by traversing the Huffman tree
// (left=0, right=1; visit left before right). 
void HuffmanTree::assignCodes(std::vector<std::pair<std::string, std::string>>& out) const {
    std::string prefix;
    assignCodesDFS(root_, prefix, out);

}

// Header writer (pre-order over leaves; "word<space>code"; newline at end).
error_type HuffmanTree::writeHeader(std::ostream& os) const {
    if (!os.good()) {
        return UNABLE_TO_OPEN_FILE_FOR_WRITING;
    }

    std::string prefix;
    writeHeaderPreorder(root_, os, prefix);

    if (os.fail()) {
        return FAILED_TO_WRITE_FILE;
    }
    return NO_ERROR;
}

// Encode a sequence of tokens using the codebook derived from this tree.
// Writes ASCII '0'/'1' and wraps lines to wrap_cols (80 by default).
error_type HuffmanTree::encode(const std::vector<std::string>& tokens, std::ostream& os_bits, int wrap_cols) const {
    if (root_ == nullptr) {
        if (tokens.empty()) {
            return NO_ERROR;
        }
        return UNABLE_TO_OPEN_FILE_FOR_WRITING;
    }

    std::vector<std::pair<std::string, std::string>> codePairs;
    assignCodes(codePairs);
    std::map<std::string, std::string> codeMap;

    for (std::size_t i = 0; i < codePairs.size(); i++) {
        codeMap[codePairs.at(i).first] = codePairs.at(i).second;
    }

    if (!os_bits.good()) {
        return UNABLE_TO_OPEN_FILE_FOR_WRITING;
    }

    std::string currentLine;
    for (std::size_t i = 0; i < tokens.size(); ++i) {
        const std::string& token = tokens.at(i);
        

        if (codeMap.find(token) == codeMap.end()) {
            return FAILED_TO_WRITE_FILE;
        }

        const std::string& code = codeMap.at(token);
        for (std::size_t j = 0; j < code.size(); ++j) {
            currentLine.push_back(code.at(j));
            if ((int)currentLine.size() == wrap_cols) {
                os_bits << currentLine << std::endl;
                currentLine.clear();
            }
        }
    }

    if (!currentLine.empty()) {
        os_bits << currentLine << std::endl;
    }

    if (os_bits.fail()) {
        return FAILED_TO_WRITE_FILE;
    }

    return NO_ERROR;
}

// helpers (decl only; defs in .cpp)
void HuffmanTree::destroy(TreeNode* n) noexcept {
    if (n == nullptr) {
        return;
    }

    destroy(n->getLeft());
    destroy(n->getRight());
    delete n;
}

void HuffmanTree::assignCodesDFS(const TreeNode* n, std::string& prefix, std::vector<std::pair<std::string, std::string>>& out) {
    if (n == nullptr) {
        return;
    }

    //if the node is a leaf, record its code
    if (n->getLeft() == nullptr && n->getRight() == nullptr) {
        std::string code;
        if (prefix.empty()) {
            code = "0";
        }
        else {
            code = prefix;
        }
        out.push_back(std::make_pair(n->getWord(), code));
        return;
    }
    
    //left child append 0
    prefix.push_back('0');
    assignCodesDFS(n->getLeft(), prefix, out);
    prefix.pop_back();

    //right child append 1
    prefix.push_back('1');
    assignCodesDFS(n->getRight(), prefix, out);
    prefix.pop_back();
}

void HuffmanTree::writeHeaderPreorder(const TreeNode* n, std::ostream& os, std::string& prefix) {
    if (n == nullptr) {
        return;
    }

    if (n->getLeft() == nullptr && n->getRight() == nullptr) {
        std::string code;
        if (prefix.empty()) {
            code = "0";
        }
        else {
            code = prefix;
        }
        os << n->getWord() << " " << code << std::endl;
        return;
    }


    prefix.push_back('0');
    writeHeaderPreorder(n->getLeft(), os, prefix);
    prefix.pop_back();

    prefix.push_back('1');
    writeHeaderPreorder(n->getRight(), os, prefix);
    prefix.pop_back();
}
