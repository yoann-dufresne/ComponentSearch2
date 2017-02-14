#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <set>


#include "Graph.hpp"


using namespace std;


#ifndef IO_HPP
#define IO_HPP

Graph<Node> load_graph (ifstream & verticies, ifstream & edges);
void save_componants (Graph<MetaNode> metagraph, Graph<Node> graph, ifstream & nodes, ofstream & componentsStream);
void save_metagraph (Graph<MetaNode> graph, ofstream & nodes, ofstream & edges);

#endif