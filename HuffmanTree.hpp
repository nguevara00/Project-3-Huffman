#ifndef HUFFMAN_TREE_HPP
#define HUFFMAN_TREE_HPP

#include <vector>
#include "TreeNode.hpp"
#include "utils.hpp"

class HuffmanTree {
public:
    // Build from BST output (lexicographic vector of (word, count)).
    static HuffmanTree buildFromCounts(const std::vector<std::pair<std::string, int>>& counts);

    HuffmanTree() = default;
    ~HuffmanTree();                         // deletes the entire Huffman tree

    //added implementation of the rest of big 5 to prevent errors when returning tree from buildFromCounts
    HuffmanTree(const HuffmanTree& other);
    HuffmanTree& operator=(const HuffmanTree& other);
    HuffmanTree(HuffmanTree&& other) noexcept;
    HuffmanTree& operator=(HuffmanTree&& other) noexcept;

    // Build a vector of (word, code) pairs by traversing the Huffman tree
    // (left=0, right=1; visit left before right). 
    void assignCodes(std::vector<std::pair<std::string, std::string>>& out) const;

    // Header writer (pre-order over leaves; "word<space>code"; newline at end).
    error_type writeHeader(std::ostream& os) const;

    // Encode a sequence of tokens using the codebook derived from this tree.
    // Writes ASCII '0'/'1' and wraps lines to wrap_cols (80 by default).
    error_type encode(const std::vector<std::string>& tokens,
        std::ostream& os_bits,
        int wrap_cols = 80) const;

private:
    TreeNode* root_ = nullptr; // owns the full Huffman tree

    // helpers (decl only; defs in .cpp)
    static void destroy(TreeNode* n) noexcept;
    static void assignCodesDFS(const TreeNode* n,
        std::string& prefix,
        std::vector<std::pair<std::string, std::string>>& out);
    static void writeHeaderPreorder(const TreeNode* n, std::ostream& os,
        std::string& prefix);
    TreeNode* copy(const TreeNode* n) const;
};

#endif // HUFFMAN_TREE_HPP
