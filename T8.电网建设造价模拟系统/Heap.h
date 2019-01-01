#pragma once

#include <iostream>
#include "Graphlnk.h"
#include "MinSpanTree.h"
using namespace std;

template<typename T, typename E>
class Heap
{
public:
	Heap(int size = DefaultVerticesNum);
	~Heap() { delete[]heap; }
	bool insert(const MSTEdgeNode<T, E>& x);
	bool extract(MSTEdgeNode<T, E>& item);
	void siftDown(int start, int end);
	void siftUp(int start);
	int length() { return currentSize; }
	bool isEmpty() { return currentSize == 0; }
	//void print();
private:
	MSTEdgeNode<T, E> *heap;
	int currentSize;
	int maxSize;
};

template<typename T, typename E>
Heap<T, E>::Heap(int size) {
	if (DefaultVerticesNum < size) {
		maxSize = size;
	}
	else {
		maxSize = DefaultVerticesNum;
	}
	heap = new MSTEdgeNode<T, E>[maxSize];
	if (heap == NULL) {
		cerr << "ÄÚ´æ·ÖÅäÊ§°Ü" << endl;
		exit(1);
	}
	currentSize = 0;
}


template<typename T, typename E>
void Heap<T, E>::siftDown(int start, int end) {
	MSTEdgeNode<T, E> temp = heap[start];
	int i = start;
	int j = 2 * i + 1;
	while (j <= end) {
		// let j become the smaller one
		if (heap[j] > heap[j + 1] && j < end)
			j++;
		if (temp <= heap[j])
			break;
		else {
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;
		}
	}
	heap[i] = temp;
}

template<typename T, typename E>
void Heap<T, E>::siftUp(int start) {
	MSTEdgeNode<T, E> temp = heap[start];
	int j = start;
	int i = (j - 1) / 2;
	while (j > 0) {
		if (heap[i] <= temp)
			break;
		else {
			heap[j] = heap[i];
			j = i;
			i = (i - 1) / 2;
		}
	}
	heap[j] = temp;
}

template<typename T, typename E>
bool Heap<T, E>::insert(const MSTEdgeNode<T, E> &item) {
	if (currentSize == maxSize) {
		cerr << "The heap is full" << endl;
		return false;
	}
	heap[currentSize] = item;
	siftUp(currentSize);
	currentSize++;
	return true;
}

template<typename T, typename E>
bool Heap<T, E>::extract(MSTEdgeNode<T, E>& item) {
	if (currentSize == 0) {
		cout << "The heap is empty" << endl;
		return false;
	}
	item = heap[0];
	heap[0] = heap[currentSize - 1];
	currentSize--;
	siftDown(0, currentSize - 1);
	return true;
}

/*
template<typename T, typename E>
void Heap<T, E>::print() {
	cout << "\n heap: ";
	for (int i = 0; i < currentSize; i++) {
		cout << heap[i] << '\t';
	}
}
*/

