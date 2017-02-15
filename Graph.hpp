#include <vector>
#include <iostream>


using namespace std;


#ifndef NODE_HPP
#define NODE_HPP

class Node {
public:
	int idx;
	vector<int> neighbors;

	Node ();
	Node (int idx);

	void print ();

	bool operator==(const Node &other) const;
};

class MetaNode : public Node {
public:

	vector<Node> subNodes;
	MetaNode ();
	void print();
};


template <typename N>
class Graph {
public:
	vector<N> nodes;

	Graph();

	N & getNodeFromIdx (int idx);
	int getEdgesNb();
	void print();
};


/* ----- Template implementations ----- */

template <typename N>
Graph<N>::Graph() {}

template <typename N>
void Graph<N>::print() {
	for (N node : nodes)
		node.print();
}

template <typename N>
N & Graph<N>::getNodeFromIdx (int idx) {
	return *(find(nodes.begin(), nodes.end(), Node(idx)));
}

template <typename N>
int Graph<N>::getEdgesNb() {
	int edgesNb = 0;
	for (N node: nodes)
		edgesNb += node.neighbors.size();
	return edgesNb / 2;
}

#endif
