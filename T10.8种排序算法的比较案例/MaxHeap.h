#pragma once

#include <iostream>
#include <vector>
using namespace std;

class Heap
{
public:
	Heap(int size);
	Heap(vector<int>& A, int size, long long& swap_times);
	~Heap() { delete[]heap; }
	//void insert(int item);
	//int extract();
	void siftDown(int start, int end, long long& swap_times);
	//void siftUp(int start);
	int length() { return currentSize; }
	bool isEmpty() { return currentSize == 0; }
	void print();
	void swap(int m, int n);
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

Heap::Heap(vector<int>& A, int size, long long& swap_times) {
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
		siftDown(currentPos, currentSize - 1, swap_times);
		currentPos--;
	}
}


void Heap::siftDown(int start, int end, long long& swap_times) {
	int temp = heap[start];
	int i = start;
	int j = 2 * i + 1;
	while (j <= end) {
		swap_times++;
		// let j become the larger one
		if (heap[j] < heap[j + 1] && j < end)
			j++;
		swap_times++;
		if (temp >= heap[j])
			break;
		else {
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;
		}
	}
	heap[i] = temp;
}


void Heap::swap(int m, int n) {
	int temp = heap[m];
	heap[m] = heap[n];
	heap[n] = temp;
}

void Heap::print() {
	for (int i = 0; i < currentSize; i++) {
		cout << heap[i] << ' ';
	}
}