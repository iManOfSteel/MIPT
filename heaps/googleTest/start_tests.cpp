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

mt19937 gen(time(0));
class test {
public:
	int type, key, ind1, ind2;
	test(int maxInd) {
		if (maxInd) {
			type = gen() % 5;
			key = gen();
			ind1 = gen() % maxInd;
			ind2 = gen() % maxInd;
		}
		else {
			type = 0;
			key = gen();
		}
	}
};
vector<test> tests;

void generateTests() {
	int n = 1000000;
	int heapsNum = 0;
	for (int i = 0; i < n; i++) {
		tests.emplace_back(heapsNum);
		if (tests.back().type == 0)
			heapsNum++;
	}
}

void testHeap(vector<IHeap> &v) {

}

int main(int argc, char ** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	generateTests();
	return RUN_ALL_TESTS();
}