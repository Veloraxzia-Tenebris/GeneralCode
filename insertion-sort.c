#include <stdio.h>

global int yeet = 0;

/* function prototypes */ 
void permute(int *, int, int);  
void swap(int*, int, int); 
void printArray(int*, int);
int insertionSort(int*);
 
 
/* swap 2 values by index */ 
inline void swap(int* arr, int a, int b) 
{ 
  int tmp = arr[a]; 
  arr[a] = arr[b]; 
  arr[b] = tmp; 
} 
 
 
/* print len elements */ 
void printArray( int* a, int len) 
{ 
	size_t i = 0; 

	yeet += insertionSort(a);

	fprintf(stdout, "[ " ); 

	for ( i=0; i< len; i++) fprintf(stdout, "%d " , a[i] ); 

	fprintf(stdout, "]\n" ); 
}
 
 
 
/* permute an array recursively */ 
void permute(int *arr, int start, int end) 
{ 
    int i; 
 
    if(start == end) /* this function is done */ 
    { 
      printArray(arr, end); 
      return; 
    } 
        permute(arr, start + 1, end); /* start at next element */ 
 
    /* permute remaining elements recursively */ 
    for(i = start + 1; i < end; i++)  
    { 
        if( arr[start] == arr[i] ) continue; /* skip */ 
  
        swap(arr, start, i); 
     
        permute(arr, start + 1, end); 
 
        swap(arr, start, i); /* restore element order */  
 
    } 
} 


int insertionSort(int* A) {
    int s = 0;
    for(int j = 1; j < length(A); j++) {
      int key = A[j];
      int i = j - 1;
      while((i >= 0) && (A[i] >= key)) {
        A[i + 1] = A[i];
        i = i - 1;
        s++;
      }
      A[i + 1] = key;
    }
    for(int j = 0; j < length(A); j++) {
      printf("%d, ", A[j]);
    }
    printf("\n%d", s);
    return s;
}

int main() {
  int A[] = {1, 2, 3, 4};
  permute(A, 0, 4);
  printf("%d", yeet);
  return 0;
}