#include <cstdio>

void mergeSort(int *start, int *finish, int *buffer) {
	if (finish - start == 1)
		return;
	int n = finish - start;
	int *mid = start + n / 2;
	mergeSort(start, mid, buffer);
	mergeSort(mid, finish, buffer);
	int *lPtr = start, *rPtr = mid, *begin = buffer;
	for (int i = 0; i < n; i++, buffer++) {
		if (rPtr == finish || (lPtr != mid && *lPtr < *rPtr)) {
			(*buffer) = *lPtr;
			lPtr++;
		}
		else {
			(*buffer) = *rPtr;
			rPtr++;
		}
	}
	buffer = begin;
	while (start != finish) {
		(*start) = (*buffer);
		buffer++;
		start++;
	}
}

int main() {
#ifdef Let4ik
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int n, m;
	int a[1000000], buf[1000000];
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n * m; i++)
		scanf("%d", &a[i]);
	mergeSort(a, a + n * m, buf);
	for (int i = 0; i < n * m; i++)
		printf("%d ", a[i]);
	return 0;
}