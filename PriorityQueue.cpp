#include "PriorityQueue.hpp"
#include <iomanip>

PriorityQueue::PriorityQueue(std::vector<TreeNode*> nodes) {
    // sort the input into internal data member

    for (std::size_t i = 0; i < nodes.size(); i++) {
        TreeNode* currentNode = nodes.at(i);
        std::size_t j = 0;
        while (j < items_.size() && higherPriority(items_.at(j), currentNode)) {
            j++;
        }
        items_.insert(items_.begin() + j, currentNode);
    }
}

std::size_t PriorityQueue::size() const noexcept {
	return items_.size();
}

bool PriorityQueue::empty() const noexcept {
    return items_.empty();
}

TreeNode* PriorityQueue::findMin() const noexcept {
    //minimum will always be the last item in the queue
    if (this->empty())
        return nullptr;
    return items_.back();
}

TreeNode* PriorityQueue::extractMin() noexcept {
    if (this->empty())
        return nullptr;
    TreeNode* minNode = items_.back();
    items_.pop_back();
    return minNode;
}

void PriorityQueue::deleteMin() noexcept {
    if (!this->empty())
        items_.pop_back();
}

void PriorityQueue::insert(TreeNode* node) {
    //linear search from the back of the queue and insert in proper priority
    std::size_t i = items_.size();
    while (i > 0 && higherPriority(node, items_.at(i - 1))) {
        i--;
    }
    items_.insert(items_.begin() + i, node);
}

void PriorityQueue::print(std::ostream& os) const {
    for (std::size_t i = 0; i < items_.size(); i++) {
        TreeNode* currentNode = items_.at(i);
        os << std::setw(10) << currentNode->getFrequency() << ' ' << currentNode->getWord() << '\n';
    }
}

bool PriorityQueue::higherPriority(const TreeNode* a, const TreeNode* b) noexcept {
    if (a->getFrequency() != b->getFrequency())
        return a->getFrequency() > b->getFrequency();
    return a->getWord() < b->getWord();             
}

bool PriorityQueue::isSorted() const {
    //priority queue should always be sorted, if this returns false there is a problem in the code
    for (std::size_t i = 1; i < items_.size(); ++i) {
        if (!higherPriority(items_[i - 1], items_[i]))
            return false;
    }
    return true;
}