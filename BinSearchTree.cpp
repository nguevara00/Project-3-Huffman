#include "BinSearchTree.hpp"

BinSearchTree::~BinSearchTree() {
    destroy(root_);
    root_ = nullptr;
}

void BinSearchTree::insert(const std::string& word) {
    root_ = insertHelper(root_, word);
}

void BinSearchTree::bulkInsert(const std::vector<std::string>& words) {
    for (std::size_t i = 0; i < words.size(); i++) {
        insert(words.at(i));
    }
}

[[nodiscard]] bool BinSearchTree::contains(std::string_view word) const noexcept {
    return findNode(root_, word) != nullptr;
}

[[nodiscard]] std::optional<int> BinSearchTree::countOf(std::string_view word) const noexcept {
    const TreeNode* node = findNode(root_, word);
    if (node == nullptr)
        return std::nullopt;
    return node->getFrequency();
}

void BinSearchTree::inorderCollect(std::vector<std::pair<std::string, int>>& out) const {
    inorderHelper(root_, out);
}

[[nodiscard]] std::size_t BinSearchTree::size() const noexcept {
    return sizeHelper(root_);
}

        
[[nodiscard]] unsigned BinSearchTree::height() const noexcept {
    return heightHelper(root_);
}

void BinSearchTree::destroy(TreeNode* node) noexcept {
    if (node == nullptr)
        return;
    destroy(node->getLeft());
    destroy(node->getRight());
    delete node;
}

TreeNode* BinSearchTree::insertHelper(TreeNode* node, const std::string& word) {
    if (node == nullptr)
        return new TreeNode(word);
    if (word < node->getWord())
        node->setLeft(insertHelper(node->getLeft(), word));
    else if (word > node->getWord())
        node->setRight(insertHelper(node->getRight(), word));
    else
        node->setFrequency(node->getFrequency() + 1);
    return node;
    }

const TreeNode* BinSearchTree::findNode(const TreeNode* node, std::string_view word) noexcept {
    if (node == nullptr)
        return nullptr;
    if (word < node->getWord())
        return findNode(node->getLeft(), word);
    if (word > node->getWord())
        return findNode(node->getRight(), word);
    return node;
    }

void BinSearchTree::inorderHelper(const TreeNode* node, std::vector<std::pair<std::string, int>>& out) {
    if (node == nullptr)
        return;
    inorderHelper(node->getLeft(), out);
    out.push_back(std::make_pair(node->getWord(), node->getFrequency()));
    inorderHelper(node->getRight(), out);
}
    
std::size_t BinSearchTree::sizeHelper(const TreeNode* node) noexcept {
    if (node == nullptr)
        return 0;
    return 1 + sizeHelper(node->getLeft()) + sizeHelper(node->getRight());
}

unsigned BinSearchTree::heightHelper(const TreeNode* node) noexcept {
    if (node == nullptr)
        return 0;
    unsigned left = heightHelper(node->getLeft());
    unsigned right = heightHelper(node->getRight());
    if (left > right) {
        return 1 + left;
    }
    return 1 + right;
}
