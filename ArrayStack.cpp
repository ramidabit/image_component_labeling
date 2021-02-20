#include <iostream>
#include "ArrayStack.h"
using namespace std;

static int STARTING_SIZE = 10;

// Creates a stack with a capacity of STARTING_SIZE
template<class T>
ArrayStack<T>::ArrayStack() {
	stack = new T[STARTING_SIZE];
	top = -1;
}

// Creates a stack with a predetermined capacity
template<class T>
ArrayStack<T>::ArrayStack(int capacity) {
	stack = new T[capacity];
	top = -1;
}

// Destructor to deallocate memory of stack
template<class T>
ArrayStack<T>::~ArrayStack() {
	delete[] stack;
}

// Returns true if the stack is empty
template<class T>
bool ArrayStack<T>::isEmpty() const {
	return top == -1;
}

// Returns the element at the top of the stack
template<class T>
T ArrayStack<T>::peek() const {
	return stack[top];
}

// Adds element to the top of the stack, doubling its length if full
template<class T>
void ArrayStack<T>::push(T element) {
	if(top == STARTING_SIZE - 1) {
		STARTING_SIZE *= 2;
		T* temp = new T[STARTING_SIZE];
		for(int i = 0; i < top; i++) {
			temp[i] = stack[i];
		}
		delete[] stack;
		stack = temp;
	}
	stack[++top] = element;
}

// Removes element from the top of the stack
template<class T>
T ArrayStack<T>::pop() {
	T topElement = stack[top];
	top--;
	return topElement;
}