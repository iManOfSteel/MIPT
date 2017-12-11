#include <iostream>
#include "IHeap.h"
#include <vector>
#include <algorithm>

class GHeap : public IHeap {
	std::vector<int> heap;

	static bool comp(int &a, int &b) {
		return a > b;
	}

public:
	GHeap() = default;
	explicit GHeap(int key) : heap(1, key) {}
	void insert(int key) override {
		heap.push_back(key);
		std::push_heap(heap.begin(), heap.end(), comp);
	}
	int getMin() override {
		return heap.front();
	}
	int extractMin() override {
		std::pop_heap(heap.begin(), heap.end(), comp);
		int result = heap.back();
		heap.pop_back();
		return result;
	}
	void meld(IHeap& other) override {
		auto second = dynamic_cast<GHeap*>(&other);
		heap.insert(heap.end(), second->heap.begin(), second->heap.end());
		std::make_heap(heap.begin(), heap.end(), comp);
		second->heap.clear();
	}
};