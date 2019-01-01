#include <string>
#include <iostream>
#include <assert.h>
using namespace std;
#pragma once

struct Candidate
{
	// since we don't know how long these elements will attain, just using string to input and operate them.
	string id;
	string name;
	string gender;
	int age;
	string type;
	Candidate *next;
	// constructor
	Candidate(Candidate* ptr = NULL) { next = ptr; }
	// overload constructor
	Candidate(string i, string n, string g, int a, string t, Candidate* ptr = NULL) 
	{
		id = i;
		name = n;
		gender = g;
		age = a;
		type = t;
		next = ptr;
	}
	// overload '=' operator
	Candidate &operator=(Candidate& candi) 
	{
		Candidate c(candi.id, candi.name, candi.gender, candi.age, candi.type);
		return c;
	}
	// a simple way for printing
	void print()
	{
		cout << id << '\t' << name << '\t' << gender << '\t' << age << '\t' << type << endl;
	}
};

class CandidateList
{
public:
	CandidateList();
	//CandidateList(string i, string n, char g, int a, string t);
	//~CandidateList();
	CandidateList& operator=(CandidateList& l);
	bool isEmpty() { return length == 0; }
	void Insert(Candidate& candi, int position);
	void Insert(Candidate& candi) { Insert(candi, length + 1); }
	Candidate* preSearchById(string id);
	// return the candidate node whose location is just before given position
	Candidate* preLocate(int position);
	Candidate* Delete(string id);
	void Traverse();
	int getLength() {return length;}
	int Exist(string id);
private:
	int length;
	Candidate* head;
};

CandidateList::CandidateList() 
{
	head = new Candidate;
	length = 0;
	head->next = NULL;
}

//CandidateList::CandidateList(string i, string n, char g, int a, string t)
//{
//	head = new Candidate(i, n, g, a, t);
//	length = 0;
//}

CandidateList& CandidateList::operator=(CandidateList& l)
{
	CandidateList newlist;
	int len = l.length;
	Candidate* from = l.head;
	Candidate* to = newlist.head;
	while (len > 0)
	{
		from = from->next;
		to = to->next;
		to = from;
		--len;
	}
	to->next = NULL;
	return newlist;
}

Candidate* CandidateList::preLocate(int position) 
{
	Candidate* current = head;
	position = (int)position;
	while (position > 1)
	{
		current = current->next;
		--position;
	}
	return current;
}


void CandidateList::Insert(Candidate& candi, int position)
{
	Candidate* p = new Candidate(candi.id, candi.name, candi.gender, candi.age, candi.type);
	Candidate* pre = preLocate(position);
	p->next = pre->next;
	pre->next = p;
	length++;
}

Candidate* CandidateList::preSearchById(string id)
{
	Candidate* candi = head;
	while (candi->next->id != id)
	{
		candi = candi->next;
	}
	if (candi->next == NULL) { cout << "没找到考号为" << id << "的考生！"; }
	else
		return candi;
}

Candidate* CandidateList::Delete(string id)
{
	Candidate* p = preSearchById(id);
	Candidate* candi = p->next;
	p->next = candi->next;
	Candidate* store = candi;
	length--;
	return store;
}

void CandidateList::Traverse()
{
	cout << endl;
	if (head->next == NULL) {
		cout << "当前表为空，请插入一些数据哦" << endl;
	}
	else {
		cout << "考号" << '\t' << "姓名" << '\t' << "性别" << '\t' << "年龄" << '\t' << "报考类别" << endl;
		Candidate* p = head;
		for (int i = 0; i < length; i++)
		{
			p = p->next;
			cout << p->id << '\t' << p->name << '\t' << p->gender << '\t' << p->age << '\t' << p->type << endl;
		}
	}
}

int CandidateList::Exist(string id) {
	Candidate* p = head;
	while (p->next != NULL) {
		p = p->next;
		if (p->id == id) {
			return 1;
		}
	}
	if (p->next == NULL) {
		return 0;
	}
}