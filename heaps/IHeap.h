#pragma once
class IHeap {
public:
	virtual void insert(int key) = 0;
	virtual int getMin() = 0;
	virtual int extractMin() = 0;
	virtual bool empty() = 0;
	virtual void meld(IHeap& other) = 0;
};