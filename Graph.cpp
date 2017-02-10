#include "Graph.hpp"




Node::Node () {

};

Node::Node (int idx) {
	this->idx = idx;
}

void Node::print() {
	cout << idx << endl;
}

bool Node::operator==(const Node &other) const {
	return this->idx == other.idx;
}

MetaNode::MetaNode () {

}


void MetaNode::print () {
	for (Node & n : subNodes) {
		cout << n.idx << " ";
	}
	cout << endl;
}

