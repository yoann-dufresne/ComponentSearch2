#include "algorithms.hpp"

#include <iostream>


vector<int> DFS (Graph<Node> & graph) {
	vector<int> dfs (graph.nodes.size(), -1);
	set<int> toAnnotate;
	for (int i=0 ; i<graph.nodes.size() ; i++)
		toAnnotate.insert(i);


	int currentIdx = 1;
	while (toAnnotate.size() > 0) {
		// Random init of the first node
		int offset = rand() % toAnnotate.size();
		set<int>::iterator it = toAnnotate.begin();
		advance(it, offset);
		int startIdx = *it;
		toAnnotate.erase(startIdx);

		// Init
		set<int> nextIdxs;
		nextIdxs.insert(startIdx);
		dfs[startIdx] = currentIdx;

		// Recursion
		while (nextIdxs.size() > 0) {
			set<int> neighbors;

			for (int nodeIdx : nextIdxs) {
				Node & node = graph.getNodeFromIdx(nodeIdx);

				for (int neiIdx : node.neighbors) {
					if (dfs[neiIdx] == -1) {
						dfs[neiIdx] = currentIdx;
						neighbors.insert(neiIdx);
						toAnnotate.erase(neiIdx);
					}
				}
			}

			nextIdxs = neighbors;
			currentIdx++;
		}
	}

	return dfs;
}


Graph<MetaNode> contract (Graph<Node> graph, vector<int> dfs) {
	Graph<MetaNode> contracted;
	vector<int> affectations (dfs.size(), -1);

	// Meta nodes creation
	int metaIdx = 0;
	for (int idx=0 ; idx<dfs.size() ; idx++) {
		if (affectations[idx] == -1) {
			// Init
			set<int> currentSet;
			currentSet.insert(idx);
			int annotation = dfs[idx];
			MetaNode mn;
			mn.idx = metaIdx++;

			while (currentSet.size() > 0) {
				// Modification for current node
				int nodeIdx = *(currentSet.begin());
				currentSet.erase(currentSet.begin());
				affectations[nodeIdx] = mn.idx;
				Node & node = graph.getNodeFromIdx(nodeIdx);
				mn.subNodes.push_back(node);

				// Adding the neighbors
				for (int neiIdx : node.neighbors)
					if (affectations[neiIdx] == -1 && dfs[neiIdx] == annotation)
						currentSet.insert(neiIdx);
			}

			contracted.nodes.push_back(mn);
		}
	}


	// MetaLinks creation
	for (MetaNode & mn : contracted.nodes) {
		set<int> metaLinks;

		for (Node & n : mn.subNodes) {
			for (int nei : n.neighbors) {
				if (affectations[nei] != mn.idx) {
					metaLinks.insert (affectations[nei]);
				}
			}
		}

		for (int nei : metaLinks) {
			mn.neighbors.push_back(nei);
		}
	}


	return contracted;
}


Graph<MetaNode> absorbFingers (Graph<MetaNode> graph) {
	vector<MetaNode> toRemove;

	// Check for removable meta nodes
	for (MetaNode & mn : graph.nodes) {
		if (mn.neighbors.size() == 1) {
			MetaNode & metaNei = graph.getNodeFromIdx(*(mn.neighbors.begin()));

			for (Node & sub : mn.subNodes)
				metaNei.subNodes.push_back(sub);
			metaNei.neighbors.erase(
				remove(metaNei.neighbors.begin(), metaNei.neighbors.end(), mn.idx),
				metaNei.neighbors.end()
			);

			toRemove.push_back(mn);
		}
	}

	// Remove metanodes
	for (MetaNode & mn : toRemove) {
		graph.nodes.erase(
			remove(graph.nodes.begin(), graph.nodes.end(), mn),
			graph.nodes.end()
		);
	}

	return graph;
}


Graph<MetaNode> filterNodes (Graph<MetaNode> graph, int threshold) {
	vector<MetaNode> toRemove;

	// Detect removable
	for (MetaNode & mn : graph.nodes) {
		if (mn.subNodes.size() <= threshold) {
			// Remove links
			for (int neiIdx : mn.neighbors) {
				MetaNode & metaNei = graph.getNodeFromIdx(neiIdx);
				metaNei.neighbors.erase(
					remove(metaNei.neighbors.begin(), metaNei.neighbors.end(), mn.idx),
					metaNei.neighbors.end()
				);
			}

			toRemove.push_back(mn);
		}
	}

	for (MetaNode & mn : toRemove) {
		graph.nodes.erase(
			remove(graph.nodes.begin(), graph.nodes.end(), mn),
			graph.nodes.end()
		);
	}

	return graph;
}





