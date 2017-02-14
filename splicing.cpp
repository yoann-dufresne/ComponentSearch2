#include "splicing.hpp"


// class Bond {
// public:
// 	int from;
// 	int to;
// };

Graph<MetaNode> splice (Graph<MetaNode> graph, bool optimize) {
	// vector<struct bond_s> toRemove;

	for (MetaNode & mn : graph.nodes) {
		// Looks for hub nodes
		if (mn.neighbors.size() > 2) {
			for (int neiIdx :  mn.neighbors) {
				MetaNode & nei = graph.getNodeFromIdx(neiIdx);


				// If the neighbor is not from the same component
				if (nei.neighbors.size() <= 2) {
					// Remove the neighbor to main node link
					nei.neighbors.erase(
						remove(nei.neighbors.begin(), nei.neighbors.end(), mn.idx),
						nei.neighbors.end()
					);
					// Remove the main node to neighbor link
					mn.neighbors.erase(
						remove(mn.neighbors.begin(), mn.neighbors.end(), nei.idx),
						mn.neighbors.end()
					);

					// optimize the nodes in the components that are not hubs
					if (optimize) {
						// TODO
					}
				}
			}
		}
	}

	return graph;
}

