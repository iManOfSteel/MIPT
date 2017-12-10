#include "gtest/gtest.h"
#include "../LeftistHeap.h"
#include "../SkewHeap.h"
#include "../BinomialHeap.h"
#include <vector>
#include <random>
#include <fstream>
#include <deque>
#include <set>
#include <ctime>
#include <exception>
using namespace std;
TEST(insertingTime, LeftistHeap) {
	int n = 1000000;
	LeftistHeap a;
	vector<int> v;
	for (int i = 0; i < n; i++)
		v.push_back(i);
	random_shuffle(v.begin(), v.end());
	for (int i = 0; i < n; i++)
		a.insert(v[i]);
}

TEST(insertingTime, SkewHeap) {
	int n = 1000000;
	SkewHeap a;
	vector<int> v;
	for (int i = 0; i < n; i++)
		v.push_back(i);
	random_shuffle(v.begin(), v.end());
	for (int i = 0; i < n; i++)
		a.insert(v[i]);
}


TEST(insertingTime, BinomialHeap) {
	int t = clock();
	int n = 1000000;
	BinomialHeap a;
	vector<int> v;
	for (int i = 0; i < n; i++)
		v.push_back(i);
	random_shuffle(v.begin(), v.end());
	for (int i = 0; i < n; i++)
		a.insert(v[i]);
}

TEST(extractingTime, LeftistHeap) {
	int n = 1000000;
	LeftistHeap a;
	vector<int> v(n);
	fstream in("test.txt", fstream::in);
	fstream in2("ans.txt", fstream::in);
	for (int i = 0; i < n; i++)
		in >> v[i];
	for (int i = 0; i < n; i++) {
		a.insert(v[i]);
		if (i) {
			int res;
			in2 >> res;
			ASSERT_EQ(a.getMin(), res);
		}
	}
	int t = clock();
	for (int i = 0; i < n ; i++) {
		int res;
		in2 >> res;
		ASSERT_EQ(a.extractMin(), res);
	}
	in.close();
	cout << endl << "Extracting time : " << double(clock() - t) / CLOCKS_PER_SEC << endl;
}

TEST(extractingTime, SkewHeap) {
	int n = 1000000;
	SkewHeap a;
	vector<int> v(n);
	fstream in("test.txt", fstream::in);
	fstream in2("ans.txt", fstream::in);
	for (int i = 0; i < n; i++)
		in >> v[i];
	for (int i = 0; i < n; i++) {
		a.insert(v[i]);
		if (i) {
			int res;
			in2 >> res;
			ASSERT_EQ(a.getMin(), res);
		}
	}
	int t = clock();
	for (int i = 0; i < n ; i++) {
		int res;
		in2 >> res;
		ASSERT_EQ(a.extractMin(), res);
	}
	in.close();
	cout << endl << "Extracting time : " << double(clock() - t) / CLOCKS_PER_SEC << endl;
}

TEST(extractingTime, BinomialHeap) {
	int n = 1000000;
	BinomialHeap a;
	vector<int> v(n);
	fstream in("test.txt", fstream::in);
	fstream in2("ans.txt", fstream::in);
	for (int i = 0; i < n; i++)
		in >> v[i];
	for (int i = 0; i < n; i++) {
		a.insert(v[i]);
		if (i) {
			int res;
			in2 >> res;
			ASSERT_EQ(a.getMin(), res);
		}
	}
	int t = clock();
	for (int i = 0; i < n ; i++) {
		int res;
		in2 >> res;
		ASSERT_EQ(a.extractMin(), res);
	}
	in.close();
	cout << endl << "Extracting time : " << double(clock() - t) / CLOCKS_PER_SEC << endl;
}

TEST(mergingTime, LeftistHeap) {
	int n = 1000000;
	LeftistHeap a, b;
	for (int i = 0; i < n; i += 2)
		a.insert(i);
	for (int i = 1; i < n; i += 2)
		b.insert(i);
	int t = clock();
	a.meld(b);
	cout << endl << "Merging time : " << double(clock() - t) / CLOCKS_PER_SEC << endl;
}

TEST(mergingTime, SkewHeap) {
	int n = 1000000;
	SkewHeap a, b;
	vector<int> v;
	for (int i = 0; i < n; i += 2)
		a.insert(i);
	for (int i = 1; i < n; i += 2)
		b.insert(i);
	int t = clock();
	a.meld(b);
	cout << endl << "Merging time : " << double(clock() - t) / CLOCKS_PER_SEC << endl;
}

TEST(mergingTime, BinomialHeap) {
	int n = 1000000;
	BinomialHeap a, b;
	vector<int> v;
	for (int i = 0; i < n; i += 2)
		a.insert(i);
	for (int i = 1; i < n; i += 2)
		b.insert(i);
	int t = clock();
	a.meld(b);
	cout << endl << "Merging time : " << double(clock() - t) / CLOCKS_PER_SEC << endl;
}


TEST(correctTest, LeftistHeap) {
	int n = 100000;
	vector<multiset<int>> vSets(n);
	vector<LeftistHeap> vHeaps(n);
	for (int i = 0; i < n; i++) {
		int num = rand() % 1000000000;
		int ind = rand() % n;
		vSets[ind].insert(num);
		vHeaps[ind].insert(num);
	}
	for (int i = 0; i < n; i++) {
		int ind1 = rand() % n, ind2 = rand() % n;
		if (ind1 == ind2)
			ind2 = (ind1 + 1) % n;
		EXPECT_EQ(vSets[ind1].empty(), vHeaps[ind1].empty());
		EXPECT_EQ(vSets[ind2].empty(), vHeaps[ind2].empty());
		int flag = rand() % 3;
		if (flag == 0) {
			if (!vHeaps[ind1].empty())
				EXPECT_EQ(*vSets[ind1].begin(), vHeaps[ind1].getMin());
		}
		else if (flag == 1) {
			if (!vHeaps[ind1].empty()) {
				vSets[ind1].erase(vSets[ind1].begin());
				vHeaps[ind1].extractMin();
			}
		}
		else {
			if (!vSets[ind1].empty() && !vSets[ind2].empty()) {
				vHeaps[ind1].meld(vHeaps[ind2]);
				while (vSets[ind2].size()) {
					vSets[ind1].insert(*vSets[ind2].begin());
					vSets[ind2].erase(vSets[ind2].begin());
				}
			}
		}
	}
}

TEST(correctTest, SkewHeap) {
	int n = 100000;
	vector<multiset<int>> vSets(n);
	vector<SkewHeap> vHeaps(n);
	for (int i = 0; i < n; i++) {
		int num = rand() % 1000000000;
		int ind = rand() % n;
		vSets[ind].insert(num);
		vHeaps[ind].insert(num);
	}
	for (int i = 0; i < n; i++) {
		int ind1 = rand() % n, ind2 = rand() % n;
		if (ind1 == ind2)
			ind2 = (ind1 + 1) % n;
		EXPECT_EQ(vSets[ind1].empty(), vHeaps[ind1].empty());
		EXPECT_EQ(vSets[ind2].empty(), vHeaps[ind2].empty());
		int flag = rand() % 3;
		if (flag == 0) {
			if (!vHeaps[ind1].empty())
				EXPECT_EQ(*vSets[ind1].begin(), vHeaps[ind1].getMin());
		}
		else if (flag == 1) {
			if (!vHeaps[ind1].empty()) {
				vSets[ind1].erase(vSets[ind1].begin());
				vHeaps[ind1].extractMin();
			}
		}
		else {
			if (!vSets[ind1].empty() && !vSets[ind2].empty()) {
				vHeaps[ind1].meld(vHeaps[ind2]);
				while (vSets[ind2].size()) {
					vSets[ind1].insert(*vSets[ind2].begin());
					vSets[ind2].erase(vSets[ind2].begin());
				}
			}
		}
	}
}

TEST(correctTest, BinomialHeap) {
	int n = 10000;
	vector<multiset<int>> vSets(n);
	vector<BinomialHeap> vHeaps(n);
	for (int i = 0; i < 100 * n; i++) {
		int num = rand() % 1000000000;
		int ind = rand() % n;
		vSets[ind].insert(num);
		vHeaps[ind].insert(num);
	}
	for (int i = 0; i < n; i++) {
		int ind1 = rand() % n, ind2 = rand() % n;
		if (ind1 == ind2)
			ind2 = (ind1 + 1) % n;
		EXPECT_EQ(vSets[ind1].empty(), vHeaps[ind1].empty());
		EXPECT_EQ(vSets[ind2].empty(), vHeaps[ind2].empty());
		int flag = rand() % 3;
		if (flag == 0) {
			if (!vHeaps[ind1].empty())
				EXPECT_EQ(*vSets[ind1].begin(), vHeaps[ind1].getMin());
		}
		else if (flag == 1) {
			if (!vHeaps[ind1].empty()) {
				vSets[ind1].erase(vSets[ind1].begin());
				vHeaps[ind1].extractMin();
			}
		}
		else {
			if (!vSets[ind1].empty() && !vSets[ind2].empty()) {
				vHeaps[ind1].meld(vHeaps[ind2]);
				while (vSets[ind2].size()) {
					vSets[ind1].insert(*vSets[ind2].begin());
					vSets[ind2].erase(vSets[ind2].begin());
				}
			}
		}
	}
}