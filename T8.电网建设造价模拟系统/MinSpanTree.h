#pragma once
#include "Graphlnk.h"

template<typename T, typename E>
struct MSTEdgeNode {
	// the form is the same as edge
	int tail, head;
	E key;
	// define the default format
	MSTEdgeNode(): tail(-1), head(-1), key(0) {}
	// overload some comparation operators
	bool operator<= (MSTEdgeNode<T, E>& R) { return key <= R.key; }
	bool operator> (MSTEdgeNode<T, E>& R) { return key > R.key; }
};


template<typename T, typename E>
class MinSpanTree
{
public:
	MSTEdgeNode<T, E>* edgevalue;
	MinSpanTree(int sz = DefaultVerticesNum - 1) : maxSize(sz), n(0) {
		edgevalue = new MSTEdgeNode<T, E>[sz];
	}
	bool InsertNode(MSTEdgeNode<T, E>& node) {
		if (n == maxSize) {
			cerr << "The MinSpanTree is full" << endl;
			return false;
		}
		else {
			edgevalue[n] = node;
			n++;
			return true;
		}
	}
protected:
	int maxSize, n;
};
 
