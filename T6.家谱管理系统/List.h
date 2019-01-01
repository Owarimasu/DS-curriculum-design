#pragma once

#include <iostream>
using namespace std;

template<typename T>
class ListNode {
public:
	ListNode(ListNode<T>* ptr = NULL) { next = ptr; }
	ListNode(const T d, ListNode<T>* ptr = NULL) { data = d; next = ptr; }
	T data;
	ListNode<T>* next;
};

template<typename T>
class List : public ListNode<T> {
public:
	List() { head = new ListNode<T>; }
	List<T>& operator=(const List<T>& l);
	void append(T d);
	void output();
	bool isEmpty() { return head->next == NULL; }
	bool isOrdered();
	ListNode<T>* getHead() const { return head; }
	int getLength();
private:
	ListNode<T>* head;
	int length;
};


template<typename T>
List<T>& List<T>::operator=(const List<T>& l)
{
	List<T> newlist = new List<T>;
	ListNode<T>* from = l.head;
	ListNode<T>* to = newlist.head;
	while (from->next != NULL) {
		to->data;
	}
}

template<typename T>
void List<T>::append(T d) {
	//if (typeid(d) != typeid(int)) { cerr << "Input type should be 'int'"; exit(1); }
	ListNode<T>* tail = head;
	while (tail->next != NULL) {
		tail = tail->next;
	}
	ListNode<T>* newnode = new ListNode<T>(d);
	tail->next = newnode;
	newnode->next = NULL;
	length++;
}

template<typename T>
void List<T>::output() {
	ListNode<T>* current = head->next;
	while (current != NULL) {
		cout << current->data << '\t';
		current = current->next;
	}
}

template<typename T>
bool List<T>::isOrdered() {
	if (getLength() <= 1) { return true; }
	else
	{
		ListNode<T>* pre = head->next;
		ListNode<T>* current = pre->next;
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
	ListNode<T>* p = head;
	while (p->next != NULL)
	{
		p = p->next;
		++len;
	}
	return len;
}

