#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <regex>
#include "Graphlnk.h"
using namespace std;

//const int maxVertexes = 100;
//const int maxEdges = 100;

struct NormalEdge {
	int from;
	int to;
	int weight;
};

bool isPositiveInterger(string s)
{
	//compile a Regex pattern to match the positive intergers
	regex pattern("^(\\+)?(\\d+)$");
	if (regex_match(s, pattern)) {
		return true;
	}
	else
		return false;
}

bool TopoSort(Graphlnk<int, int>& G, Graphlnk<int, int>& StorePath) {
	int vertexNum, num, from, to, weight, v1, v2;
	int v, w;
	int top = -1;
	string input_1, input_2;
	cin >> input_1;
	cin >> input_2;
	if (!isPositiveInterger(input_1)) {
		cout << "交接点的总数应该为正整数";
		return false;
	}
	if (!isPositiveInterger(input_2)) {
		cout << "任务数量应该为正整数";
		return false;
	}
	vertexNum = stoi(input_1);
	num = stoi(input_2);
	NormalEdge* StoreEdge = new NormalEdge[num];
	int EdgeNum = 0;
	int* Indegree = new int[vertexNum];
	// initialize the Indegree[]
	for (int i = 0; i < vertexNum; i++) {
		Indegree[i] = 0;
	}
	//getchar();
	while (num > 0) {
		cin >> from >> to >> weight;
		if (!G.insertVertex(from) || !G.insertVertex(to)) {
			cout << "顶点数超过了图的最大储存";
			return false;
		}
		v1 = G.getVertexPos(from);
		v2 = G.getVertexPos(to);
		if (!G.insertEdge(v1, v2, weight)) {
			cout << from << "->" << to << " 这条边插入失败";
			return false;
		}
		StoreEdge[EdgeNum].from = from;
		StoreEdge[EdgeNum].to = to;
		StoreEdge[EdgeNum].weight = weight;
		EdgeNum++;
		Indegree[v2]++;	
		num--;
	}
	// put vertexes that indegree is 0 to the stack
	for (int i = 0; i < vertexNum; i++) {
		if (Indegree[i] == 0) {
			Indegree[i] = top;
			top = i;
		}
	}
	// will generate the path in vertexNum's times
	for (int i = 0; i < vertexNum; i++) {
		if (top == -1) {
			cout << "有回路" << endl;
			return false;
		}
		else {
			// pop the stack to get the sort
			v = top;
			top = Indegree[top];
			int vertex = G.getValue(v);
			cout << vertex << '\t';
			// create a graph to store the vertexes after topoSort
			StorePath.insertVertex(vertex);
			w = G.getFirstNeighbor(v);
			while (w != -1) {
				if (--Indegree[w] == 0) {
					Indegree[w] = top;
					top = w;
				}
				w = G.getNextNeighbor(v, w);
			}
		}
	}
	// insert the remaining edges to StorePath graph
	for (int i = 0; i < EdgeNum; i++) {
		int from = StoreEdge[i].from;
		int to = StoreEdge[i].to;
		int weight = StoreEdge[i].weight;
		int v1 = StorePath.getVertexPos(from);
		int v2 = StorePath.getVertexPos(to);
		StorePath.insertEdge(v1, v2, weight);
	}
	return true;
}


void CriticalPath(Graphlnk<int, int>& G) {
	int i, j, k, Ae, Al, w;
	int n = G.getNumVertices();
	int count = 0;
	// The earliest start time of each events
	int* Ve = new int[n];
	// The latest allowable start time of each events
	int* Vl = new int[n];
	// The earliest start time of each activities
	//Edge<int, int>* Ae = new Edge<int, int>[];
	// The latest allowable start time of each activities
	//Edge<int, int>* Al = new Edge<int, int>[maxEdges];
	for (i = 0; i < n; i++) {
		Ve[i] = 0;
	}
	for (i = 0; i < n; i++) {
		j = G.getFirstNeighbor(i);
		while (j != -1) {
			w = G.getWeight(i, j);
			if (Ve[i] + w > Ve[j]) {
				Ve[j] = Ve[i] + w;
			}
			j = G.getNextNeighbor(i, j);
		}
	}
	for (i = 0; i < n; i++) {
		Vl[i] = Ve[n - 1];
	}
	// calculate reversely
	for (j = n - 2; j >= 0; j--) {
		k = G.getFirstNeighbor(j);
		while (k != -1) {
			w = G.getWeight(j, k);
			if (Vl[k] - w < Vl[j]) {
				Vl[j] = Vl[k] - w;
			}
			k = G.getNextNeighbor(j, k);
		}
	}
	
	for (i = 0; i < n; i++) {
		j = G.getFirstNeighbor(i);
		while (j != -1) {
			Ae = Ve[i];
			Al = Vl[j] - G.getWeight(i, j);
			if (Al == Ae) {
				cout << G.getValue(i) << " ->" << G.getValue(j) << endl;
				count++;
			}
			j = G.getNextNeighbor(i, j);
		}
	}
	delete[]Ve;
	delete[]Vl;
}


int main() {
	Graphlnk<int, int> G, StorePath;
	if (!TopoSort(G, StorePath)) {
		cout << endl << "0" << endl;
	}
	CriticalPath(StorePath);
}
