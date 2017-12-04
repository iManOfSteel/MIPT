#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>
using namespace std;
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
	std::vector<T> head, tail;
	void normalize() {
		size_t n = head.size() + tail.size();
		if (tail.size() > 2 * head.size()) {
			reverse(tail.begin(), tail.end());
			reverse(head.begin(), head.end());
			while (head.size() < n / 2) {
				head.push_back(tail.back());
				tail.pop_back();
			}
			reverse(tail.begin(), tail.end());
			reverse(head.begin(), head.end());
		}
		else if (head.size() > 2 * tail.size()) {
			reverse(tail.begin(), tail.end());
			reverse(head.begin(), head.end());
			while (tail.size() < n / 2) {
				tail.push_back(head.back());
				head.pop_back();
			}
			reverse(tail.begin(), tail.end());
			reverse(head.begin(), head.end());
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