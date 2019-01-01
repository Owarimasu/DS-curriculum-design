#pragma once

#include <iostream>
#include <string>
using namespace std;

struct TreeNode
{
public:
	string name;
	TreeNode *firstChild;
	TreeNode *nextSibling;
	TreeNode() {
		firstChild = NULL;
		nextSibling = NULL;
	}
	TreeNode(string str) {
		name = str;
		firstChild = NULL;
		nextSibling = NULL;
	}
	void addChild(string str) {
		TreeNode* child = new TreeNode(str);
		if (firstChild == NULL) {
			firstChild = child;
		}
		else
		{
			TreeNode* lastChild = firstChild;
			while (lastChild->nextSibling != NULL) {
				lastChild = lastChild->nextSibling;
			}
			lastChild->nextSibling = child;
		}
	}
	void addSibling(string str) {
		TreeNode* sibling = new TreeNode(str);
		TreeNode* lastSibling = this;
		while (lastSibling->nextSibling != NULL) {
			lastSibling = lastSibling->nextSibling;
		}
		lastSibling->nextSibling = sibling;
	}
	void printChild() {
		TreeNode* child = firstChild;
		while (child->nextSibling != NULL) {
			cout << child->name <<'\t';
			child = child->nextSibling;
		}
		cout << child->name;
	}
};


class FamiTree: public TreeNode
{
public:
	FamiTree() { root = current = NULL; }
	FamiTree(TreeNode* r);
	//~FamiTree();
	// make the current node to be root, the following are the same
	bool Root() { return root; }
	bool FirstChild();
	bool NextSibling();
	bool Parent(TreeNode* c, TreeNode* p);
	//bool PreviousSibling(TreeNode* c, TreeNode* p);
	bool Find(string s, TreeNode* p);
	//void DeleteSubTree(TreeNode* p);
	void pre_traversal(TreeNode* root);
	TreeNode *root, *current;
};


FamiTree::FamiTree(TreeNode* r) {
	root = new TreeNode(r->name);
	current = root;
}


bool FamiTree::FirstChild() {
	if (current->firstChild == NULL || current == NULL) {
		current = NULL;
		return false;
	}
	else {
		current = current->firstChild;
		return true;
	}
}

bool FamiTree::NextSibling() {
	if (current->nextSibling == NULL || current == NULL) {
		current = NULL;
		return false;
	}
	else {
		current = current->nextSibling;
		return true;
	}
}

// find the current node's parent node
bool FamiTree::Parent(TreeNode* c, TreeNode* p) {
	TreeNode* q = p->firstChild;
	while (q != NULL && q != c) {
		if (Parent(c, q)) 
			return true;
		q = q->nextSibling;
	}
	if (q != NULL && q == c) {
		current = p;
		return true;
	}
	else
	{
		current = NULL;
		return false;
	}

}



// find a node in a tree whose root is p
bool FamiTree::Find(string s, TreeNode* p) {
	if (p->name == s) {
		current = p;
		return true;
	}
	else {
		TreeNode* q = p->firstChild;
		while (!(q == NULL)) {
			if (Find(s, q)) {
				return true;
			}
			else {
				q = q->nextSibling;
			}
		}
	}
	return false;
}





void FamiTree::pre_traversal(TreeNode* root) {
	if (root != NULL) {
		cout << root->name << '\t';
		pre_traversal(root->firstChild);
		pre_traversal(root->nextSibling);
	}
}