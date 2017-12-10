#include "IHeap.h"
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
class SHNode {
public:
	SHNode *left, *right;
	int key;
	SHNode(int key): key(key) {
		left = right = NULL;
	}
	~SHNode() {
		delete left;
		delete right;
	}
};
class SkewHeap : public IHeap {
	SHNode *root;
public:
	SkewHeap() {
		root = NULL;
	}
	SkewHeap(int key) {
		root = new SHNode(key);
	}
	~SkewHeap() {
		delete root;
	}
	int key(SHNode *node) {
		return node == 0 ? 0 : node->key;
	}
	bool empty() override {
		return root == NULL;
	}
	SHNode* merge(SHNode *first, SHNode *second) {
		if (!first || !second)
			return second == NULL ? first : second;
		if (first->key > second->key)
			swap(first, second);
		first->right = merge(first->right, second);
		swap(first->left, first->right);
		return first;
	}
	void insert(int key) override {
		root = merge(root, new SHNode(key));
	}
	int getMin() override {
		return key(root);
	}
	int extractMin() override {
		int ret = getMin();
		SHNode *_root = root;
		root = merge(root->left, root->right);
		_root->left = _root->right = NULL;
		delete _root;
		return ret;
	}
	void meld(IHeap &_other) override {
		SkewHeap *other = dynamic_cast<SkewHeap*>(&_other);
		root = merge(other->root, root);
		other->root = NULL;
		return;
	}
};