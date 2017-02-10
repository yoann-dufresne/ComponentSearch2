#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

#include "Graph.hpp"


using namespace std;


#ifndef IO_HPP
#define IO_HPP

Graph<Node> load_graph (ifstream & verticies, ifstream & edges);

#endif