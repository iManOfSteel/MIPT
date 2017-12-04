#include "gtest/gtest.h"
#include "deque.h"
#include <exception>
TEST(push_back_tests, test1) {
	Deque<int> d;
	d.push_back(228);
	EXPECT_EQ(228, d.back());
}

TEST(push_back_tests, test2) {
	Deque<int> d;
	d.push_back(228);
	d.push_back(-1213);
	EXPECT_EQ(-1213, d.back());
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
	Deque<int> d;
	int n = 17;
	for (int i = 0; i < n; i++)
		d.push_back(n - i - 1);
	sort(d.begin(), d.end());
	int i = 0;
	for (Deque<int>::iterator it = d.begin(); it != d.end(); it++, i++)
		EXPECT_EQ(i, *it);
}