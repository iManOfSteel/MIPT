#include <iostream>
#include <vector>
#include <string>

using namespace std;

class BigInteger {
public:
	bool isNegative;
	vector<int> v;
	BigInteger() {
		isNegative = false;
	}
	BigInteger(int a) {
		isNegative = false;
		if (a < 0) {
			isNegative = true;
			a *= -1;
		}
		while (a) {
			v.push_back(a % 10);
			a /= 10;
		}
	}
	BigInteger(const BigInteger &a): isNegative(a.isNegative), v(a.v) {}
	string toString() const;
	BigInteger& operator=(const BigInteger &a);
	BigInteger& operator-=(const BigInteger& other);
	BigInteger& operator+=(const BigInteger& other);
	BigInteger& operator*=(const BigInteger& other);
	BigInteger& operator/=(const BigInteger& other);
	BigInteger& operator%=(const BigInteger& other);
	BigInteger& operator++();
	BigInteger& operator--();
	BigInteger operator++(int);
	BigInteger operator--(int);
	BigInteger operator-() const;
	BigInteger div2() const;
	BigInteger friend operator+(const BigInteger &a, const BigInteger &b);
	BigInteger friend operator-(const BigInteger &a, const BigInteger &b);
	BigInteger friend operator*(const BigInteger &a, const BigInteger &b);
	BigInteger friend operator/(const BigInteger &a, const BigInteger &b);
	BigInteger friend operator%(const BigInteger &a, const BigInteger &b);
	bool friend operator<=(const BigInteger &a, const BigInteger &b);
	bool friend operator==(const BigInteger &a, const BigInteger &b);
	bool friend operator!=(const BigInteger &a, const BigInteger &b);
	bool friend operator<(const BigInteger &a, const BigInteger &b);
	bool friend operator>=(const BigInteger &a, const BigInteger &b);
	bool friend operator>(const BigInteger &a, const BigInteger &b);
	explicit operator bool();
};

BigInteger abs(const BigInteger &a) {
	BigInteger res(a);
	res.isNegative = false;
	return res;
}
string BigInteger::toString() const {
	if ((int)this->v.size() == 0)
		return "0";
	string res = "";
	if (this->isNegative)
		res = "-";
	for (int i = (int)this->v.size() - 1 ; i >= 0; i--)
		res += this->v[i] + '0';
	return res;
}
ostream& operator<<(ostream& out, const BigInteger& number) {
	out << number.toString();
	return out;
}
istream& operator>>(istream& in, BigInteger& number) {
	number.v.clear();
	number.isNegative = false;
	string s;
	in >> s;
	if (s == "0" || s == "-0")
		return in;
	if (s[0] == '-')
		number.isNegative = true;
	for (int i = (int)s.size() - 1; i >= 0 && s[i] != '-'; i--)
		number.v.push_back(s[i] - '0');
	return in;
}
bool operator<=(const BigInteger &a, const BigInteger &b) {
	if (a.v.size() == 0 && b.v.size() == 0)
		return true;
	if (a.isNegative && !b.isNegative)
		return true;
	if (!a.isNegative && b.isNegative)
		return false;
	bool more = (a.v.size() > b.v.size());
	for (int i = (int)a.v.size() - 1; a.v.size() == b.v.size() && i >= 0 && !more && a.v[i] >= b.v[i]; i--)
		more = a.v[i] > b.v[i];
	return (more ^ (!a.isNegative));
}
bool operator==(const BigInteger &a, const BigInteger &b) {
	return (a <= b && b <= a);
}
bool operator!=(const BigInteger &a, const BigInteger &b) {
	return !(a == b);
}
bool operator<(const BigInteger &a, const BigInteger &b) {
	return (a <= b && a != b);
}
bool operator>=(const BigInteger &a, const BigInteger &b) {
	return !(a < b);
}
bool operator>(const BigInteger &a, const BigInteger &b) {
	return !(a <= b);
}
BigInteger::operator bool() {
	return ((*this) != 0);
}

BigInteger& BigInteger::operator=(const BigInteger &a) {
	isNegative = a.isNegative;
	v = a.v;
	return *(this);
}
BigInteger& BigInteger::operator-=(const BigInteger& other) {
	BigInteger second(other);
	if (isNegative == other.isNegative) {
		if (((*this) < other) ^ isNegative) {
			swap(v, second.v);
			isNegative ^= 1;
		}
		for (int i = 0; i < (int)v.size(); i++) {
			if (i < (int)second.v.size())
				v[i] -= second.v[i];
			if (v[i] < 0) {
				v[i] += 10;
				v[i + 1]--;
			}
		}
		while (v.size() && v.back() == 0)
			v.pop_back();
	}
	else {
		second.isNegative ^= 1;
		(*this) += second;
	}
	return (*this);
}
BigInteger& BigInteger::operator+=(const BigInteger& other) {
	if (isNegative == other.isNegative) {
		int add = 0;
		for (int i = 0; i < (int)max(v.size(), other.v.size()) || add; i++) {
			if (i < (int)other.v.size())
				add += other.v[i];
			if (i < (int)v.size()) {
				v[i] += add;
				add = v[i] / 10;
				v[i] %= 10;
			}
			else {
				v.push_back(add % 10);
				add /= 10;
			}
		}
	}
	else {
		BigInteger second(other);
		second.isNegative ^= 1;
		(*this) -= second;
	}
	return (*this);
}
BigInteger& BigInteger::operator*=(const BigInteger& other) {
	if (other == 0 || (*this) == 0)
		return (*this) = 0;
	BigInteger res(0);
	res.v.resize(v.size() + other.v.size() - 1);
	for (int i = 0; i < (int)other.v.size(); i++)
		for (int j = 0; j < (int)v.size(); j++)
			res.v[i + j] += other.v[i] * v[j];
	int add = 0;
	for (int i = 0; i < (int)res.v.size() || add; i++) {
		if (i == (int)res.v.size())
			res.v.push_back(0);
		res.v[i] += add;
		add = res.v[i] / 10;
		res.v[i] %= 10;
	}
	swap(v, res.v);
	isNegative ^= other.isNegative;
	return (*this);
}
BigInteger& BigInteger::operator/=(const BigInteger& other) {
	BigInteger second(other);
	BigInteger l = 0, r = abs(*this) + 1;
	while (r - l > 1) {
		BigInteger m = (l + r).div2();
		if (abs(m * other) > abs(*this))
			r = m;
		else l = m;
	}
	v = l.v;
	isNegative ^= other.isNegative;
	return (*this);
}
BigInteger& BigInteger::operator%=(const BigInteger& other) {
	BigInteger res = (*this) - ((*this) / other) * other;
	v = res.v;
	isNegative = res.isNegative;
	return (*this);
}
BigInteger& BigInteger::operator++() {
	(*this) += 1;
	return (*this);
}
BigInteger& BigInteger::operator--() {
	return (*this);
	(*this) -= 1;
	return (*this);
}
BigInteger BigInteger::operator++(int) {
	BigInteger res(*this);
	++(*this);
	return res;
}
BigInteger BigInteger::operator--(int) {
	BigInteger res(*this);
	--(*this);
	return res;
}
BigInteger BigInteger::operator-() const {
	BigInteger res(*this);
	if (*this != 0)
		res.isNegative ^= 1;
	return res;
}
BigInteger operator+(const BigInteger &a, const BigInteger &b) {
	BigInteger res(a);
	res += b;
	return res;
}
BigInteger operator-(const BigInteger &a, const BigInteger &b) {
	BigInteger res(a);
	res -= b;
	return res;
}
BigInteger operator*(const BigInteger &a, const BigInteger &b) {
	BigInteger res(a);
	res *= b;
	return res;
}
BigInteger operator/(const BigInteger &a, const BigInteger &b) {
	BigInteger res(a);
	res /= b;
	return res;
}
BigInteger operator%(const BigInteger &a, const BigInteger &b) {
	BigInteger res(a);
	res %= b;
	return res;
}
BigInteger BigInteger::div2() const {
	BigInteger res(*this);
	int add = 0;
	for (int i = v.size() - 1; i >= 0; i--) {
		res.v[i] += add * 10;
		add = res.v[i] % 2;
		res.v[i] /= 2;
	}
	while (res.v.size() && res.v.back() == 0)
		res.v.pop_back();
	return res;
}