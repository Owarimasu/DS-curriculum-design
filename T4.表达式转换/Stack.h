#pragma once
#include <iostream>
#include <regex>
#include <string>
const int DEFAULT_SIZE = 50;
using namespace std;

template <typename T>
class Stack
{
public:
	Stack();
	~Stack();
	void push(const T& x);
	T pop();
	T getTop() { return _elem[top]; };
	bool isEmpty() { return top == -1; };
	bool isFull() { return top == size; };
	int Length() { return top; }
	void expand();
	void print();
private:
	T * _elem;
	int top;
	int size = DEFAULT_SIZE;
};

template <typename T>
Stack<T>::Stack()
{
	_elem = new T[size + 1];
	top = -1;
}

template <typename T>
Stack<T>::~Stack()
{
	delete[] _elem;
	top = -1;
}


template <typename T>
void Stack<T>::push(const T& x)
{
	if (isFull())
	{
		expand();
	}
	_elem[++top] = x;
}

template <typename T>
T Stack<T>::pop()
{
	if (top == -1)
	{
		cerr << "Stack underflow!";
		exit(1);
	}
	else
	{
		T top_item = _elem[top];
		top--;
		return top_item;
	}
}

template <typename T>
void Stack<T>::expand()
{
	T* newArray = new T[2 * size + 1];
	if (newArray == NULL)
	{
		cerr << "Allocate Error!" << endl;
		exit(1);
	}
	for (int i = 0; i <= size; i++)
	{
		newArray[i] = _elem[i];
	}
	cout << "Expand successfully!" << endl;
	size *= 2;

	delete[]_elem;
	_elem = newArray;
}


template <typename T>
void Stack<T>::print()
{
	for (int i = top; i >= 0; i--)
	{
		cout << _elem[i];
		if (i != 0) cout << " ";
	}
}

