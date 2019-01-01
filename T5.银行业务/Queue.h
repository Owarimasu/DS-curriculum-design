#pragma once

#include <iostream>
using namespace std;

template <typename T>
struct Node {
	Node(Node<T>* ptr = NULL) { next = ptr; }
	Node(const T& d, Node<T>* ptr = NULL) { data = d; next = ptr; }
	T data;
	Node<T>* next;
};

template <typename T>
class Queue
{
public:
	Queue() {
		head = new Node<T>();
		tail = head;
	}
	//~Queue() { makeEmpty(); }
	void EnQueue(T d);
	T DeQueue();
	bool isEmpty() { return head == tail; }
	void makeEmpty();
	void print();
private:
	Node<T>* head;
	Node<T>* tail;
};

template<typename T>
void Queue<T>::EnQueue(T d)
{
	Node<T>* item = new Node<T>(d);
	tail->next = item;
	item->next = NULL;
	tail = item;
}

template<typename T>
T Queue<T>::DeQueue()
{
	if (head == tail) {
		cerr<<"队列没有数据，不能出队！";
		exit(1);
	}
	Node<T>* item = head->next;
	// only one element in the queue
	if (head->next == tail) {
		head->next = NULL;
		tail = head;
	}
	else {
		head->next = item->next;
	}
	return item->data;
}

template<typename T>
void Queue<T>::makeEmpty()
{
	if (head->next == tail || head == tail)
	{
		delete tail;
	}
	else
	{
		Node<T>* item = head;
		while (item != tail) {
			Node<T>* p = item->next;
			delete item;
			item = p;
		}
		delete item;
	}

}

template<typename T>
void Queue<T>::print()
{
	Node<T>* item = head->next;
	while (item->next != NULL) {
		cout << item->data << " ";
		item = item->next;
	}
	// avoid the last blank
	cout << item->data;
}