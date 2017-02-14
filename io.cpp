#include "io.hpp"



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


void save_componants (Graph<MetaNode> metagraph, Graph<Node> graph, ifstream & nodes, ofstream & componentsStream) {
	// Init
	set<int> toCompute;
	for (MetaNode & mn : metagraph.nodes) {
		toCompute.insert(mn.idx);
	}


	// Assignations
	int compIdx = 0;
	vector<int> components (graph.nodes.size(), -1);
	vector<int> metaNodes (graph.nodes.size(), -1);
	while (toCompute.size() > 0) {
		// Select a first metanode to assign
		set<int> currentComponent;
		currentComponent.insert(*(toCompute.begin()));
		toCompute.erase(toCompute.begin());

		// BFS to search for all the elements of the current component
		while (currentComponent.size() > 0) {
			// Get a meta note in the waiting set
			int metaIdx = *(currentComponent.begin());
			currentComponent.erase(currentComponent.begin());
			MetaNode & mn = metagraph.getNodeFromIdx(metaIdx);

			// Perform assignations
			for (Node & n : mn.subNodes) {
				components[n.idx] = compIdx;
				metaNodes[n.idx] = mn.idx;
			}

			// Add neighbors
			for (int neiIdx : mn.neighbors) {
				if (toCompute.find(neiIdx) != toCompute.end()) {
					currentComponent.insert(neiIdx);
					toCompute.erase(neiIdx);
				}
			}
		}

		compIdx++;
	}

	// Save components
	string line;
	getline(nodes, line);
	componentsStream << line << ";metanode;component" << endl;

	for (int i=0 ; i<graph.nodes.size() ; i++) {
		getline(nodes, line);
		componentsStream << line << ";" << metaNodes[i] << ";" << components[i] << endl;
	}
}


void save_metagraph (Graph<MetaNode> graph, ofstream & nodes, ofstream & edges) {
	nodes << "node;size" << endl;
	edges << "from;to" << endl;

	for (MetaNode & mn : graph.nodes) {
		nodes << mn.idx << ";" << mn.subNodes.size() << endl;

		for (int neiIdx : mn.neighbors) {
			if (neiIdx > mn.idx)
				edges << mn.idx << ";" << neiIdx << endl;
		}
	}
}









