/*
 * This class uses a one-dimensional array to represent a stack, and
 * uses templates to allow for the creation of stacks of any object type.
 */

#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include <iostream>
using namespace std;

template<class T>
class ArrayStack {
	private:
		T* stack;    // Dyanmically allocated array of objects
		int top;     // Index of top element in stack
	public:
		ArrayStack();
		ArrayStack(int capacity);
		~ArrayStack();
		bool isEmpty() const;
		T peek() const;
		void push(T element);
		T pop();
};

#endif