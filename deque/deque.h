//https://github.com/iManOfSteel/MIPT/tree/master/deque
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

template<class T>
class Vector {
public:
	T* v;
	size_t tsize, _size;
	Vector() {
		tsize = 0;
		_size = 4;
		v = new T[4];
	}
	~Vector() {
		delete[] v;
	}
	size_t size() const {
		return tsize;
	}
	bool empty() const {
		return tsize == 0;
	}
	void normalize() {
		if (tsize == _size || (_size > 4 && _size >= 4 * tsize)) {
			T* temp = new T[2 * tsize];
			memcpy(temp, v, sizeof(T) * tsize);
			swap(temp, v);
			_size = 2 * tsize;
			delete[] temp;
		}
	}
	T& back() {
		return v[tsize - 1];
	}
	const T& back() const {
		return v[tsize - 1];
	}
	T pop_back() {
		T ret = v[tsize - 1];
		tsize--;
		normalize();
		return ret;
	}
	void push_back(T& val) {
		v[tsize++] = val;
		normalize();
	}
	T& operator[](size_t n) {
		return v[n];
	}
	const T& operator[](size_t n) const {
		return v[n];
	}
	void operator=(const Vector &V) {
		_size = V._size;
		tsize = V.tsize;
		delete[] v;
		v = new T[_size];
		memcpy(v, V.v, sizeof(T) * tsize);
	}
	void reverse() {
		for (int i = 0; i < (int)tsize / 2; i++)
			swap(v[i], v[tsize - i - 1]);
	}
};

template<class Deque, class T>
class base_iterator : public std::iterator<std::random_access_iterator_tag, T> {
public:
	size_t pos;
	Deque* ptr;
	base_iterator(Deque *d, size_t pos): pos(pos), ptr(d) {
	}
	base_iterator() {
		ptr = NULL;
		pos = 0;
	}
	base_iterator(const base_iterator &arg) {
		pos = arg.pos;
		ptr = arg.ptr;
	}
	base_iterator& operator+=(size_t n) {
		pos += n;
		return (*this);
	}
	base_iterator& operator-=(size_t n) {
		pos -= n;
		return (*this);
	}
	base_iterator& operator++() {
		pos++;
		return (*this);
	}
	base_iterator& operator++(int) {
		base_iterator temp(*this);
		pos++;
		return temp;
	}
	base_iterator& operator--() {
		pos--;
		return (*this);
	}
	base_iterator& operator--(int) {
		base_iterator temp(*this);
		pos--;
		return temp;
	}
	base_iterator operator+(const size_t n) const {
		base_iterator temp(*this);
		temp += n;
		return temp;
	}
	base_iterator operator-(const size_t n) const {
		base_iterator temp(*this);
		temp -= n;
		return temp;
	}
	int operator-(const base_iterator &arg) const {
		return pos - arg.pos;
	}
	int operator+(const base_iterator &arg) const {
		return pos + arg.pos;
	}
	T* operator->() {
		return &((*ptr)[pos]);
	}
	T& operator*() {
		return (*ptr)[pos];
	}
	T& operator[](int n) {
		return (*ptr)[pos + n];
	}
	bool operator==(const base_iterator &arg) const {
		return (pos == arg.pos && ptr == arg.ptr);
	}
	bool operator!=(const base_iterator &arg) const {
		return !((*this) == arg);
	}
	bool operator<=(const base_iterator &arg) const {
		return (pos <= arg.pos);
	}
	bool operator<(const base_iterator &arg) const {
		return (pos < arg.pos);
	}
};

template<class T>
class Deque {
	Vector<T> head, tail;
	void normalize() {
		size_t n = head.size() + tail.size();
		if (tail.size() > 2 * head.size()) {
			tail.reverse();
			head.reverse();
			while (head.size() < n / 2) {
				head.push_back(tail.back());
				tail.pop_back();
			}
			tail.reverse();
			head.reverse();
		}
		else if (head.size() > 2 * tail.size()) {
			tail.reverse();
			head.reverse();
			while (tail.size() < n / 2) {
				tail.push_back(head.back());
				head.pop_back();
			}
			tail.reverse();
			head.reverse();
		}
	}
public:
	typedef base_iterator<Deque, T> iterator;
	typedef base_iterator<const Deque, const T> const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	iterator begin() noexcept {
		return iterator(this, 0);
	}
	iterator end() noexcept {
		return iterator(this, size());
	}
	const_iterator cbegin() const noexcept {
		return const_iterator(this, 0);
	}
	const_iterator cend() const noexcept {
		return const_iterator(this, size());
	}
	reverse_iterator rbegin() noexcept {
		return std::reverse_iterator<iterator>(end());
	}
	reverse_iterator rend() noexcept {
		return std::reverse_iterator<iterator>(begin());
	}
	const_reverse_iterator crbegin() const noexcept {
		return std::reverse_iterator<const_iterator>(cend());
	}
	const_reverse_iterator crend() const noexcept {
		return std::reverse_iterator<const_iterator>(cbegin());
	}
	const_iterator begin() const noexcept {
		return cbegin();
	}
	const_iterator end() const noexcept {
		return cend();
	}
	const_reverse_iterator rbegin() const noexcept {
		return crbegin();
	}
	const_reverse_iterator rend() const noexcept {
		return crend();
	}
	T& back() {
		if (tail.size())
			return tail.back();
		else return head.back();
	}
	T& front() {
		if (head.size())
			return head.back();
		else return tail.back();
	}
	const T& back() const {
		if (tail.size())
			return tail.back();
		else return head.back();
	}
	const T& front() const {
		if (head.size())
			return head.back();
		else return tail.back();
	}
	Deque<T>() {}
	Deque<T>(const Deque<T> &arg) {
		head = arg.head;
		tail = arg.tail;
	}
	size_t size() const {
		return head.size() + tail.size();
	}
	bool empty() const {
		return size() == 0;
	}
	void push_back(T val) {
		tail.push_back(val);
		normalize();
	}
	void push_front(T val) {
		head.push_back(val);
		normalize();
	}
	T pop_back() {
		T ret;
		if (tail.size()) {
			ret = tail.back();
			tail.pop_back();
		}
		else {
			ret = head.back();
			head.pop_back();
		}
		normalize();
		return ret;
	}
	T pop_front() {
		T ret;
		if (head.size()) {
			ret = head.back();
			head.pop_back();
		}
		else {
			ret = tail.back();
			tail.pop_back();
		}
		normalize();
		return ret;
	}
	T& operator[](const int n) {
		if (n < (int)head.size())
			return head[head.size() - n - 1];
		else return tail[(n - head.size())];
	}
	const T& operator[](const int n) const {
		if (n < (int)head.size())
			return head[head.size() - n - 1];
		else return tail[(n - head.size())];
	}
};