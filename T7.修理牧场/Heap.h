#pragma once

#include <iostream>
using namespace std;

class Heap
{
public:
	Heap(int size);
	Heap(int A[], int size);
	~Heap() { delete[]heap; }
	void insert(int item);
	int extract();
	void siftDown(int start, int end);
	void siftUp(int start);
	int length() { return currentSize; }
	bool isEmpty() { return currentSize==0; }
	void print();
private:
	int* heap;
	int currentSize;
};

Heap::Heap(int size) {
	heap = new int[size];
	if (heap == NULL) {
		cerr << "ÄÚ´æ·ÖÅäÊ§°Ü" << endl;
		exit(1);
	}
	currentSize = 0;
}

Heap::Heap(int A[], int size) {
	heap = new int[size];
	if (heap == NULL) {
		cerr << "ÄÚ´æ·ÖÅäÊ§°Ü" << endl;
		exit(1);
	}
	for (int i = 0; i < size; i++) {
		heap[i] = A[i];
	}
	currentSize = size;
	// find the fisrt place that need to adjust
	int currentPos = (currentSize - 2) / 2;
	while (currentPos >= 0) {
		siftDown(currentPos, currentSize - 1);
		currentPos--;
	}
}


void Heap::siftDown(int start, int end) {
	int temp = heap[start];
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

void Heap::siftUp(int start) {
	int temp = heap[start];
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

void Heap::insert(int item) {
	heap[currentSize] = item;
	siftUp(currentSize);
	currentSize++;
}

int Heap::extract() {
	if (currentSize == 0) {
		cout << "The heap is empty" << endl;
	}
	int top = heap[0];
	heap[0] = heap[currentSize - 1];
	currentSize--;
	siftDown(0, currentSize - 1);
	return top;
}

void Heap::print() {
	cout << "\n heap: ";
	for (int i = 0; i < currentSize; i++) {
		cout << heap[i] << '\t';
	}
}