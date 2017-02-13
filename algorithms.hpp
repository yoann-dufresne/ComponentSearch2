#include <vector>
#include <set>
#include <map>
#include <algorithm>

#include "Graph.hpp"

using namespace std;

#ifndef ALGOS_HPP
#define ALGOS_HPP

vector<int> DFS (Graph<Node> & graph);
Graph<MetaNode> contract (Graph<Node> graph, vector<int> dfs);
Graph<MetaNode> absorbFingers (Graph<MetaNode> graph);
Graph<MetaNode> filterNodes (Graph<MetaNode> graph, int nodeThreshold);
Graph<MetaNode> filterEdges (Graph<MetaNode> graph, int edgeThreshold, int originalSize);

#endif