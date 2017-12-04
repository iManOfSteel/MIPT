#include <iostream>

using namespace std;

class Permutation {
public:
	unsigned int n;
	int *a;
	Permutation(): n(0), a(NULL) {}
	explicit Permutation(unsigned int n): n(n), a(new int[n]) {
		for (unsigned int i = 0; i < n; i++)
			a[i] = i;
	}
	Permutation(unsigned int n, int *a1): n(n), a(new int[n]) {
		for (unsigned int i = 0; i < n; i++)
			a[i] = a1[i];
	}
	Permutation(const Permutation& other): n(other.n), a(new int[n]) {
		for (unsigned int i = 0; i < n; i++)
			a[i] = other.a[i];
	}
	~Permutation() {
		delete[] a;
	}
	void operator()(int *array);
	Permutation next();
	Permutation previous();
	Permutation inverse();
	Permutation& operator*=(const Permutation& other);
	Permutation& operator++();
	Permutation& operator--();
	Permutation operator++(int);
	Permutation operator--(int);
	Permutation& operator=(const Permutation& other) {
		if (n == other.n && other == (*this))
			return (*this);
		n = other.n;
		delete[] a;
		a = new int[n];
		for (unsigned int i = 0; i < n; i++)
			a[i] = other.a[i];
		return (*this);
	}
	bool friend operator<=(const Permutation &left, const Permutation &right);
	bool friend operator==(const Permutation &left, const Permutation &right);
	bool friend operator!=(const Permutation &left, const Permutation &right);
	bool friend operator<(const Permutation &left, const Permutation &right);
	bool friend operator>=(const Permutation &left, const Permutation &right);
	bool friend operator>(const Permutation &left, const Permutation &right);
	int operator[](unsigned int pos);
	Permutation friend operator*(const Permutation& first, const Permutation& second);
};
int min(int a, int b) {
	if (a < b)
		return a;
	return b;
}
ostream& operator<<(ostream &os, const Permutation& per) {
	for (unsigned int i = 0; i < per.n; i++)
		os << per.a[i] << ' ';
	return os;
}
void Permutation::operator()(int *array) {
	int * temp = new int[n];
	for (unsigned int i = 0; i < n; i++)
		temp[i] = array[i];
	for (int i = 0 ; i < (int)n; i++)
		array[a[i]] = temp[i];
	delete[] temp;
}
Permutation Permutation::next() {
	Permutation res(*this);
	++res;
	return res;
}
Permutation Permutation::previous() {
	Permutation res(*this);
	--res;
	return res;
}
Permutation Permutation::inverse() {
	Permutation res(*this);
	for (unsigned int i = 0; i < n; i++)
		res.a[a[i]] = i;
	return res;
}
Permutation& Permutation::operator*=(const Permutation &other) {
	Permutation temp(*this);
	for (unsigned int i = 0; i < n; i++)
		a[i] = temp.a[other.a[i]];
	return (*this);
}
Permutation& Permutation::operator++() {
	int pos = n - 2;
	for (; pos >= 0 && a[pos] > a[pos + 1]; pos--);
	if (pos == -1) {
		for (unsigned int i = 0; i < n; i++)
			a[i] = i;
	}
	else {
		for (int i = n - 1; i > pos; i--)
			if (a[i] > a[pos]) {
				swap(a[i], a[pos]);
				break;
			}
		for (int i = pos + 1, j = n - 1; i < (int)j; i++, j-- )
			swap(a[i], a[j]);
	}
	return (*this);
}
Permutation& Permutation::operator--() {
	int pos = n - 2;
	for (; pos >= 0 && a[pos] < a[pos + 1]; pos--);
	if (pos == -1) {
		for (unsigned int i = 0; i < n; i++)
			a[i] = n - i - 1;
	}
	else {
		for (int i = n - 1; i > pos; i--)
			if (a[i] < a[pos]) {
				swap(a[i], a[pos]);
				break;
			}
		for (int i = pos + 1, j = n - 1; i < (int)j; i++, j-- )
			swap(a[i], a[j]);
	}
	return (*this);
}
Permutation Permutation::operator++(int) {
	Permutation res(*this);
	++(*this);
	return res;
}
Permutation Permutation::operator--(int) {
	Permutation res(*this);
	--(*this);
	return res;
}
Permutation operator*(const Permutation& first, const Permutation& second) {
	Permutation res(first);
	res *= second;
	return res;
}
bool operator<=(const Permutation &left, const Permutation &right) {
	for (unsigned int i = 0; i < left.n; i++)
		if (left.a[i] != right.a[i])
			return left.a[i] <= right.a[i];
	return true;
}
bool operator==(const Permutation &left, const Permutation &right) {
	return (left <= right && right <= left);
}
bool operator!=(const Permutation &left, const Permutation &right) {
	return !(left == right);
}
bool operator<(const Permutation &left, const Permutation &right) {
	return (left <= right && left != right);
}
bool operator>=(const Permutation &left, const Permutation &right) {
	return !(left < right);
}
bool operator>(const Permutation &left, const Permutation &right) {
	return !(left <= right);
}
int Permutation::operator[](unsigned int pos) {
	return a[pos];
}