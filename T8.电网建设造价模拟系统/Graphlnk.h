#pragma once

#include <iostream>
using namespace std;

const int DefaultVerticesNum = 50;

template<typename T, typename E>
struct Edge {
	// dest means the other vertex of the edge(the position in table)
	T dest;
	// cost means the weight
	E cost;
	// pointer to the next edge
	Edge* link;
	Edge() {
		dest = -1;
		cost = 0;
		link = NULL;
	}
	Edge(T num, E weight) {
		dest = num;
		cost = weight;
		link = NULL;
	}
	bool operator!= (Edge& R) const {
		return (dest != R.dest) ? true : false;
	}
};

template<typename T, typename E>
struct Vertex {
	T data;
	Edge<T, E>* adj;
};

template<typename T, typename E>
// int this question, T == char, E == int;
class Graphlnk
{
public:
	Graphlnk();
	//Graphlnk(int size);
	//~Graphlnk();
	int getNumVertices() { return numVertices; }
	int getNumEdges() { return numEdges; }
	T getValue(int i) {
		return (i >= 0 && i < numVertices) ? NodeTable[i].data : '0';
	}
	E getWeight(int v1, int v2);
	bool insertVertex(const T& vertex);
	//bool removeVertex(int v);
	bool insertEdge(int v1, int v2, E cost);
	//bool removeEdge(int v1, int v2);
	int getFirstNeighbor(int v);
	int getNextNeighbor(int v, int w);
	int getVertexPos(const T vertex) {
		for (int i = 0; i < numVertices; i++) {
			if (NodeTable[i].data == vertex) {
				return i;
			}
		}
		return -1;
	}

private:
	Vertex<T, E> *NodeTable;
	int numVertices;
	int maxVertices;
	int numEdges;
};


template<typename T, typename E>
Graphlnk<T, E>::Graphlnk() {
	maxVertices = DefaultVerticesNum;
	numEdges = 0;
	numVertices = 0;
	NodeTable = new Vertex<T, E>[maxVertices];
	if (NodeTable == NULL) {
		cerr << "ÄÚ´æ·ÖÅä´íÎó" << endl;
		exit(1);
	}
	for (int i = 0; i < maxVertices; i++) {
		NodeTable[i].adj = NULL;
	}
}

template<typename T, typename E>
int Graphlnk<T, E>::getFirstNeighbor(int v) {
	if (v != -1) {
		Edge<T, E>* p = NodeTable[v].adj;
		if (p != NULL) 
			return p->dest;
	}
	return -1;
}

template<typename T, typename E>
int Graphlnk<T, E>::getNextNeighbor(int v, int w) {
	if (v != -1) {
		Edge<T, E>* p = NodeTable[v].adj;
		while (p != NULL && p->dest != w) {
			p = p->link;
		}
		if (p != NULL && p->link != NULL) {
			return p->link->dest;
		}
	}
	return -1;
}

template<typename T, typename E>
E Graphlnk<T, E>::getWeight(int v1, int v2) {
	if (v1 != -1 && v2 != -1) {
		Edge<T, E>* p = NodeTable[v1].adj;
		while (p != NULL && p->dest != v2) {
			p = p->link;
		}
		if (p != NULL) {
			return p->cost;
		}
	}
	return 0;
}



template<typename T, typename E>
bool Graphlnk<T, E>::insertVertex(const T& vertex) {
	if (numVertices == maxVertices) {
		return false;
	}
	else {
		NodeTable[numVertices].data = vertex;
		numVertices++;
		return true;
	}
}



template<typename T, typename E>
bool Graphlnk<T, E>::insertEdge(int v1, int v2, E weight) {
	if (v1 >= 0 && v1 < numVertices&&v2 >= 0 && v2 < numVertices) {
		Edge<T, E>* q;
		Edge<T, E>* p = NodeTable[v1].adj;
		// to find whether this edge exists
		while (p != NULL && p->dest != v2) {
			p = p->link;
		}
		if (p != NULL) {
			return 0;
		}
		p = new Edge<T, E>;
		q = new Edge<T, E>;
		// insert p from the start position
		p->dest = v2;
		p->cost = weight;
		p->link = NodeTable[v1].adj;
		NodeTable[v1].adj = p;
		// insert q from the start position
		q->dest = v1;
		q->cost = weight;
		q->link = NodeTable[v2].adj;
		NodeTable[v2].adj = q;
		numEdges++;
		return true;
	}
	else {
		return false;
	}
}
