#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include "Graph.hpp"
#include "io.hpp"
#include "algorithms.hpp"
#include "splicing.hpp"


using namespace std;



int main (int argc, char * argv[]) {

	// --- Default parameters ---
	string nodesFilename = "nodes.csv";
	string edgesFilename = "edges.csv";
	string basename = "";
	int nodeFilter = 0;
	int edgeFilter = 0;
	int seed = time(0);
	bool optimizeComponents = false;


	// --- Arguments parsing ---
	for (int idx=1 ; idx<argc ; idx++) {
		if (argv[idx][0] == '-') {
			switch (argv[idx][1]) {
			case 'n':
				nodesFilename = string(argv[++idx]);
				break;
			case 'e':
				edgesFilename = string(argv[++idx]);
				break;
			case 'b':
				basename = string(argv[++idx]);
				break;
			case 'N':
				nodeFilter = atoi(argv[++idx]);
				break;
			case 'E':
				edgeFilter = atoi(argv[++idx]);
				break;
			case 'o':
				optimizeComponents = true;
				break;
			case 'r':
				seed = atoi(argv[++idx]);
				break;

			default:
				break;
			}
		}
	}

	// Init random generator
	srand(seed);


	// --- Loading ---
	cout << "--- Loading ---" << endl;

	ifstream nodesFile (nodesFilename.c_str());
	if (!nodesFile) {
		cerr << "The file " << nodesFilename << " seems to be missing." << endl;
		return 1;
	}

	ifstream edgesFile (edgesFilename.c_str());
	if (!edgesFile) {
		cerr << "The file " << edgesFilename << " seems to be missing." << endl;
		return 1;
	}

	Graph<Node> graph = load_graph(nodesFile, edgesFile);
	cout << graph.nodes.size() << " nodes loaded " << endl;



	// --- Algorithms ---
	cout << endl << "--- Run algorithms ---" << endl;
	cout << "-> DFS..." << endl;
	vector<int> dfs = DFS (graph);

	cout << "-> Contraction..." << endl;
	Graph<MetaNode> contracted = contract (graph, dfs);
	cout << contracted.nodes.size() << " nodes in the contracted graph" << endl;

	cout << "-> Absorb fingers..." << endl;
	contracted = absorbFingers (contracted);
	cout << contracted.nodes.size() << " nodes in the contracted graph" << endl;


	cout << endl << "--- Filtering ---" << endl;
	cout << "-> Filtering nodes..." << endl;
	Graph<MetaNode> filtered = filterNodes (contracted, nodeFilter);

	cout << "-> Filtering edges..." << endl;
	filtered = filterEdges (filtered, nodeFilter, graph.nodes.size());
	cout << filtered.nodes.size() << " nodes in the filtered graph" << endl;



	// --- Splicing ---
	cout << endl << "--- Splicing ---" << endl;
	Graph<MetaNode> spliced = splice (filtered, false);


	// --- Output ---
	cout << endl << "--- Saving results ---" << endl;
	cout << "-> Saving components" << endl;
	stringstream ss;
	ss << basename << "components.csv";
	ofstream outStream (ss.str());
	ifstream inStream (nodesFilename);
	// Graph<MetaNode> metagraph, Graph<Node> graph, ifstream & nodes, ofstream & componentsStream
	save_componants (spliced, graph, inStream, outStream);



	cout << endl << "--- Program ended ---" << endl;

	return 0;
}
