#include <stdio.h>

int factorial(int);

int factorial(int x) {
	if(x < 2) {
		return 1;
	} else {
		return (x * factorial(x - 1));
	}
}

int main() {
	int out = 0;
	for(int i = 0; i < 9; i++) {
		out = factorial(i);
		printf("%d! = %d\n", i, out);
	}
	return 0;
}