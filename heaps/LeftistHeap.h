#include "IHeap.h"
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
class LHNode {
public:
	LHNode *left, *right;
	int key, dist;
	LHNode(int key): key(key) {
		dist = 1;
		left = right = NULL;
	}
	~LHNode() {
		delete left;
		delete right;
	}
};
class LeftistHeap : public IHeap {
	LHNode *root;
public:
	LeftistHeap() {
		root = NULL;
	}
	LeftistHeap(int key) {
		root = new LHNode(key);
	}
	~LeftistHeap() {
		delete root;
	}
	bool empty() override {
		return root == NULL;
	}
	int dist(LHNode *node) {
		return node == NULL ? 0 : node->dist;
	}
	int key(LHNode *node) {
		return node == 0 ? 0 : node->key;
	}
	LHNode* merge(LHNode *first, LHNode *second) {
		if (!first || !second)
			return second == NULL ? first : second;
		if (key(first) > key(second))
			swap(first, second);
		first->right = merge(first->right, second);
		if (dist(first->right) > dist(first->left))
			swap(first->right, first->left);
		first->dist = dist(first->right) + 1;
		return first;
	}
	void insert(int key) override {
		root = merge(root, new LHNode(key));
	}
	int getMin() override {
		return key(root);
	}
	int extractMin() override {
		int ret = getMin();
		LHNode *_root = root;
		root = merge(root->left, root->right);
		_root->left = _root->right = NULL;
		delete _root;
		return ret;
	}
	void meld(IHeap &_other) override {
		LeftistHeap *other = dynamic_cast<LeftistHeap*>(&_other);
		root = merge(other->root, root);
		other->root = NULL;
		return;
	}
};