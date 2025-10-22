#ifndef IMPLEMENTATION_TREENODE_HPP
#define IMPLEMENTATION_TREENODE_HPP

#include <string>
#include <iostream>

class TreeNode {
public:
	//constructors
	TreeNode(const std::string& str, int num) : frequency_(num), word_(str), left_(nullptr), right_(nullptr) {}
	TreeNode(const std::string& str) : frequency_(1), word_(str), left_(nullptr), right_(nullptr) {}

	//getters for data
	
	int getFrequency() const {
		return frequency_;
	}

	const std::string& getWord() const {
		return word_;
	}

	//setters for data

	void setFrequency(int num) {
		frequency_ = num;
	}

	void setWord(const std::string& str) {
		word_ = str;
	}

	//getters and setters for children

	TreeNode* getLeft() const {
		return left_;
	}

	TreeNode* getRight() const {
		return right_;
	}

	void setLeft(TreeNode* left) {
		left_ = left;
	}

	void setRight(TreeNode* right) {
		right_ = right;
	}

	void print() const {
		std::cout << "(" << getWord() << ", " << getFrequency() << ")" << std::endl;
	}

private:
	int frequency_;
	std::string word_;
	TreeNode* left_;
	TreeNode* right_;
};

#endif //IMPLEMENTATION_TREENODE_HPP