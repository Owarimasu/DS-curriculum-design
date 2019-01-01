#pragma once

#include <iostream>
using namespace std;

template<typename T>
class Node {
public:
	Node(Node<T>* ptr = NULL) { next = ptr; }
	Node(const T d, Node<T>* ptr = NULL) { data = d; next = ptr; }
	T data;
	Node<T>* next;
};

template<typename T>
class List : public Node<T> {
public:
	List() { head = new Node<T>; }
	List<T>& operator=(const List<T>& l);
	void append(T d);
	void output();
	bool isEmpty() { return head->next == NULL; }
	bool isOrdered();
	Node<T>* getHead() const { return head; }
	int getLength();
private:
	Node<T>* head;
	int length;
};


template<typename T>
List<T>& List<T>::operator=(const List<T>& l)
{
	List<T> newlist = new List<T>;
	Node<T>* from = l.head;
	Node<T>* to = newlist.head;
	while (from->next != NULL) {
		to->data;
	}
}

template<typename T>
void List<T>::append(T d) {
	//if (typeid(d) != typeid(int)) { cerr << "Input type should be 'int'"; exit(1); }
	Node<T>* tail = head;
	while (tail->next != NULL) {
		tail = tail->next;
	}
	Node<T>* newnode = new Node<T>(d);
	tail->next = newnode;
	newnode->next = NULL;
	length++;
}

template<typename T>
void List<T>::output() {
	Node<T>* current = head->next;
	while (current != NULL) {
		cout << current->data << ' ';
		current = current->next;
	}
}

template<typename T>
bool List<T>::isOrdered() {
	if (getLength() <= 1) { return true; }
	else
	{
		Node<T>* pre = head->next;
		Node<T>* current = pre->next;
		while (current != NULL) {
			if (current->data < pre->data) {
				return false;
			}
			else {
				pre = current;
				current = current->next;
			}
		}
		return true;
	}
}

template<typename T>
int List<T>::getLength()
{
	int len = 0;
	Node<T>* p = head;
	while (p->next!=NULL)
	{
		p = p->next;
		++len;
	}
	return len;
}