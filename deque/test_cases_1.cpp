#include "gtest/gtest.h"
#include "deque.h"
#include <vector>
#include <random>
#include <deque>
#include <exception>
using namespace std;
TEST(push_back_tests, test1) {
	Deque<int> d;
	d.push_back(228);
	EXPECT_EQ(228, d.back());
}

TEST(push_back_tests, test2) {
	Deque<int> d;
	d.push_back(22);
	d.push_back(-1213);
	EXPECT_EQ(-1213, d.back());
}

TEST(push_back_tests, test3) {
	Deque<int> D;
	deque<int> d;
	vector<int> v;
	int n = 272;
	for (int i = 0; i < n; i++) {
		if (d.size() && rand() % 2) {
			d.pop_back();
			D.pop_back();
		}
		if (d.size() && rand() % 2) {
			d.pop_front();
			D.pop_front();
		}
		else {
			d.push_front(i);
			D.push_front(i);
		}
		EXPECT_EQ(d.size(), D.size());
		for (int i = 0; i < d.size(); i++)
			EXPECT_EQ(d[i], D[i]);
	}
}

TEST(iterator_tests, begin_to_end) {
	Deque<int> d;
	int n = 17;
	for (int i = 0; i < n; i++)
		d.push_back(i);
	int i = 0;
	for (Deque<int>::iterator it = d.begin(); it != d.end(); it++, i++)
		EXPECT_EQ(i, *it);
}

TEST(iterator_tests, sort) {
	std::vector<int> v;
	Deque<int> d;
	int n = 17000;
	for (int i = 0; i < n; i++)
		v.push_back(n - i - 1);
	random_shuffle(v.begin(), v.end());
	for (int i = 0; i < n; i++)
		d.push_back(v[i]);
	sort(d.begin(), d.end());
	int i = 0;
	for (Deque<int>::iterator it = d.begin(); it != d.end(); it++, i++)
		EXPECT_EQ(i, *it);
}

TEST(iterator_tests, reverse_sort) {
	std::vector<int> v;
	Deque<int> d;
	int n = 17000;
	for (int i = 0; i < n; i++)
		v.push_back(n - i - 1);
	random_shuffle(v.rbegin(), v.rend());
	for (int i = 0; i < n; i++)
		d.push_back(v[i]);
	sort(d.rbegin(), d.rend());
	int i = 0;
	for (Deque<int>::iterator it = d.begin(); it != d.end(); it++, i++)
		EXPECT_EQ(n - 1 - i, *it);
}

TEST(iterator_tests, const_iterators) {
	Deque<int> d;
	for (int i = 0; i < 10; i++)
		d.push_front(i);
	Deque<int>::const_iterator it1 = d.cbegin();
	Deque<int>::const_reverse_iterator it2 = d.crbegin();
	Deque<int>::const_iterator it3 = d.cend();
	Deque<int>::const_reverse_iterator it4 = d.crend();
}

TEST(vector_tests, reverse) {
	vector<int> v;
	Vector<int> V;
	int n = 22000;
	for (int i = 0; i < n; i++) {
		v.push_back(i);
		V.push_back(i);
	}
	reverse(v.begin(), v.end());
	V.reverse();
	for (int i = 0; i < n; i++)
		EXPECT_EQ(v[i], V[i]);
	EXPECT_EQ(v.size(), V.size());
}

TEST(time_test, max_test) {
	Deque<int> d;
	int n = 10000000;
	for (int i = 0; i < n; i++) {
		d.push_back(i);
	}
	while (!d.empty())
		if (rand() % 2)
			d.pop_front();
		else d.pop_back();
}