#include <iostream>
#include <sstream>
#include <string>
#include "List.h"
using namespace std;


void IstreamMess(List<int> list, string str)
{
	stringstream ss;
	ss << str;
	string s;
	while (ss >> s) {
		if (stoi(s) == -1)
			break;
		else
			list.append(stoi(s));
	}
}

bool Intersection(List<int> l1, List<int> l2)
{
	int num = 0;
	Node<int>* p1 = l1.getHead();
	Node<int>* p2 = l2.getHead();
	Node<int>* pre = p1;
	p1 = p1->next;
	p2 = p2->next;
	// contains empty list, just end the program and print "NULL"
	if (p1 == NULL || p2 == NULL) {
		return 0;
	}
	else {
		while (p1 != NULL && p2 != NULL) {
			if (p1->data > p2->data) {
				p2 = p2->next;
			}
			else if (p1->data < p2->data) {
				pre->next = p1->next;
				p1 = p1->next;
			}
			else
			{
				p1 = p1->next;
				pre = pre->next;
				p2 = p2->next;
				num++;
			}
		}

		// list2 go to the end, so the ramaining part of list1 should be delete
		if (p2 == NULL ) {
			pre->next = NULL;
		}
		if (num == 0) {
			return 0;
		}
		else {
			return 1;
		}
	}
}

int main()
{
	List<int> list1, list2;
	string s1, s2;
	cout << "请输入第一串序列（以-1结尾，否则默认回车结束）：";
	getline(cin, s1);
	cout << "请输入第二串序列：";
	getline(cin, s2);
	IstreamMess(list1, s1);
	IstreamMess(list2, s2);
	if (!(list1.isOrdered() && list2.isOrdered()))
		cout << "输入的序列不符合非降序要求";
	else {
		if (Intersection(list1, list2)) {
			list1.output();
		}
		else {
			cout << "NULL";
		}
	}
}