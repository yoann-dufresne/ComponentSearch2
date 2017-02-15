#include "splicing.hpp"



Graph<MetaNode> splice (Graph<MetaNode> graph, bool optimize) {
	for (MetaNode & mn : graph.nodes) {
		set<int> neiToRemove;

		// Looks for hub nodes
		if (mn.neighbors.size() > 2) {
			for (int neiIdx : mn.neighbors) {
				MetaNode & nei = graph.getNodeFromIdx(neiIdx);


				// If the neighbor is not from the same component
				if (nei.neighbors.size() <= 2) {
					// Remove the neighbor to main node link
					nei.neighbors.erase(
						remove(nei.neighbors.begin(), nei.neighbors.end(), mn.idx),
						nei.neighbors.end()
					);

					neiToRemove.insert(neiIdx);

					// optimize the nodes in the components that are not hubs
					if (optimize) {
						// TODO
					}
				}
			}
		}

		for (int idx : neiToRemove) {
			// Remove the main node to neighbor link
			mn.neighbors.erase(
				remove(mn.neighbors.begin(), mn.neighbors.end(), idx),
				mn.neighbors.end()
			);
		}
	}

	return graph;
}

