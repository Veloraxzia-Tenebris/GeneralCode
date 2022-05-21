#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Needed for Windows sleep
// Use other for UNIX
//#include <unistd.h>
#include <Windows.h>

// Doubly-linked list structure
struct node {
	int key;
	struct node* next;
	struct node* prev;
};

// Function to make new node
struct node* newNode(int key) {
	struct node* temp = (struct node*) malloc(sizeof(struct node));
	temp -> key = key;
	temp -> next = NULL;
	temp -> prev = NULL;
	return temp;
}

// Function to count the length of a list
int countList(struct node* list) {
	// Set counter pointer to head
	struct node* ptr = list;
	// Create output variable
	int out = 1;
	// Check for empty list
	if(!(ptr -> key)) {
		return -1;
	}
	// Loop through the list till NULL
	while((ptr -> next) != NULL) {
		out++;
		ptr = ptr -> next;
	}
	return out;
}

// Function to print each linked list
void printList(struct node* list) {
	// Set counter pointer to head
	struct node* ptr = list;
	// Check for empty list
	if(!(ptr -> key)) {
		printf("The list is empty.\n");
	}
	printf("[");
	// Loop through the list till NULL
	while((ptr -> next) != NULL) {
		printf("%d, ", ptr -> key);
		ptr = ptr -> next;
	}
	printf("%d", ptr -> key);
	printf("]\n");
}

// Function to insert new node at the end of the list
void insertList(struct node* list, int key) {
	// Set counter pointer to head
	struct node* ptr = list;
	// Loop to the end of the list
	while((ptr -> next) != NULL) {
		ptr = ptr -> next;
	}
	// Create a new node
	struct node* temp = newNode(key);
	// Re-link head and new node
	temp -> prev = ptr;
	ptr -> next = temp;
}

// Debugging and testing routine
int main() {
	// Create a linked list starting node
	struct node* list = newNode(1);
	// Insert elements
	insertList(list, 2);
	insertList(list, 1);
	insertList(list, 3);
	insertList(list, 4);
	// Print and count the elements
	printList(list);
	printf("The list is %d long.\n", countList(list));
	return 0;
}