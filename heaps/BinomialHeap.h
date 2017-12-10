#include "IHeap.h"
#include <algorithm>
#include <iostream>
#include <list>

using namespace std;

class BHItem {
public:
	BHItem *child, *sibling;
	int degree, key;
	BHItem() {
		child = sibling = NULL;
		degree = key = 0;
	}
	BHItem(int key): key(key) {
		degree = 1;
		child = sibling = NULL;
	}
	~BHItem() {
		delete child;
		delete sibling;
	}
};

class BinomialHeap : public IHeap {
public:
	BHItem *root, *_min;
	BinomialHeap() {
		root = _min = NULL;
	}
	BinomialHeap(int key) {
		root = _min = new BHItem(key);
	}
	~BinomialHeap() {
		delete root;
	}
	bool empty() override {
		return root == NULL;
	}
	void updateMin() {
		BHItem *temp = root;
		while (temp) {
			if (!_min || temp->key < _min->key)
				_min = temp;
			temp = temp->sibling;
		}
	}
	void mergeRoots(BHItem *other) {
		BHItem* tRoot = root, *prevRoot = NULL;
		while (tRoot && other) {
			while (other && tRoot->degree > other->degree) {
				if (prevRoot)
					prevRoot->sibling = other;
				else root = other;
				BHItem *temp = other->sibling;
				other->sibling = tRoot;
				prevRoot = other;
				other = temp;
			}
			prevRoot = tRoot;
			tRoot = tRoot->sibling;
		}
		if (other)
			prevRoot->sibling = other;
	}
	void relaxRoots() {
		BHItem *tRoot = root, *prev = NULL;
		while (tRoot && tRoot->sibling) {
			if (tRoot->degree == tRoot->sibling->degree && !(tRoot->sibling->sibling && tRoot->sibling->degree == tRoot->sibling->sibling->degree)) {
				if (tRoot->key < tRoot->sibling->key) {
					BHItem *temp = tRoot->sibling;
					tRoot->sibling = temp->sibling;
					tRoot->degree *= 2;
					temp->sibling = tRoot->child;
					tRoot->child = temp;
				}
				else {
					if (prev)
						prev->sibling = tRoot->sibling;
					else root = tRoot->sibling;
					BHItem* temp = tRoot->sibling;
					tRoot->sibling = temp->child;
					temp->child = tRoot;
					temp->degree *= 2;
					tRoot = temp;
				}
			}
			else {
				prev = tRoot;
				tRoot = tRoot->sibling;
			}
		}
	}
	void meld(IHeap& _other) override {
		BinomialHeap *other = dynamic_cast<BinomialHeap*>(&_other);
		if (root == NULL)
			return void((*this) = (*other));
		mergeRoots(other->root);
		relaxRoots();
		other->root = other->_min = NULL;
		updateMin();
	}
	void insert(int key) override {
		if (root == NULL)
			return void(_min = root = new BHItem(key));
		BinomialHeap temp(key);
		meld(temp);
	}
	int getMin() override {
		return _min->key;
	}
	int extractMin() override {
		int res = _min->key;
		BHItem *temp = root;
		while (temp && temp->sibling != _min)
			temp = temp->sibling;
		if (temp)
			temp->sibling = _min->sibling;
		else root = _min->sibling;
		temp = _min->child;
		_min->sibling = _min->child = NULL;
		delete _min;
		_min = NULL;
		BHItem *prev = NULL, *next = NULL;
		while (temp) {
			next = temp->sibling;
			temp->sibling = prev;
			prev = temp;
			temp = next;
		}
		BinomialHeap tempHeap;
		tempHeap.root = prev;
		meld(tempHeap);
		tempHeap.root = tempHeap._min = NULL;
		if (!_min)
			updateMin();
		return res;
	}
};

