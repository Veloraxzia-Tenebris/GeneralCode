#include <algorithm>
#include <string>
#include <array>
#include <iostream>

void printArray(int* A, int len) {
	std::cout << "[";
	for(int i = 0; i < len; i++) {
		printf("%d, ", A[i]);
	}
	std::cout << "\b\b";
	std::cout << "]";
}

int insertionSort(int* A, int len) {
	int key = 0;
	int s = 0;
	int i = 0;
	int j = 0;
	for(i = 1; i < len; i++) {
		key = A[i];
		j = i - 1;
		while(A[j] > key) {
			A[j + 1] = A[j];
			j--;
			s++;
		}
		A[j + 1] = key;
	}
	printArray(A, len);
	printf("\n%d", s);
	return s;
}

int main() {
	int A[4] = {4, 3, 2, 1};
	int len = sizeof(A) / sizeof(int);
	int i = 0;
	int s = 0;
	/*
	while(std::next_permutation(A, A + 4)) {
		s = insertionSort(A, len);
		i++;
	}
	*/
	double out = (double)s / (double)i;
	printf("%f", out);
	return 0;
}