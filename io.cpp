#include "io.hpp"

#include <sstream>


vector<string> split (string & line, char delim);

Graph<Node> load_graph (ifstream & verticies, ifstream & edges) {
	Graph<Node> g;

	// First line verticies
	string line;
	getline(verticies, line);

	// All the lines
	int i=0;
	while (verticies) {
		getline(verticies, line);
		if (verticies && line.size() > 0) {
			g.nodes.push_back(Node(i++));
		}
	}


	// first line of edges
	getline(edges, line);
	vector<string> tokens = split(line, ';');
	// Find the idx of the targets and sources in the header
	int srcIdx = -1, tgtIdx = -1;
	for (int idx=0 ; idx<tokens.size() ; idx++) {
		// To lower case
		transform(tokens[idx].begin(), tokens[idx].end(), tokens[idx].begin(), ::tolower);

		if (tokens[idx] == "source") {
			srcIdx = idx;
		} else if (tokens[idx] == "target") {
			tgtIdx = idx;
		}
	}

	if (srcIdx == -1 || tgtIdx == -1) {
		cerr << "Source or Target label absent from the edges csv file" << endl;
		return g;
	}

	// All the lines
	while (edges) {
		getline (edges, line);

		if (edges && line.size() > 0) {
			// Get the idxs of the nodes from the edge
			vector<string> strs = split(line, ';');
			int idx1 = atoi(strs[srcIdx].c_str());
			int idx2 = atoi(strs[tgtIdx].c_str());

			// Set the neighbors
			g.nodes[idx1].neighbors.push_back(idx2);
			g.nodes[idx2].neighbors.push_back(idx1);
		}
	}


	return g;
}


// Split a string into multiple strings using the delim char as a separator
vector<string> split (string & line, char delim) {
	vector<string> strs;

	string token;
	stringstream ss;
	ss << line;
	while (ss) {
		getline(ss, token, delim);

		if (ss)
			strs.push_back(token);
	}

	return strs;
}
