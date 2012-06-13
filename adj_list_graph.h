/*
 * adj_list_graph.h
 *
 *  Created on: Jun 2, 2012
 *      Author: enzam
 */

#ifndef ADJ_LIST_GRAPH_H_
#define ADJ_LIST_GRAPH_H_

using namespace std;
#include <vector>
#include "graph.h"

struct AdjListGraph : public Graph {
	vector< vector<int> > adjList;
	AdjListGraph(int n) {
		adjList = vector< vector<int> >(n);
	}

	void addEdge(int id, int ch, bool biDirEdge = false) {
		adjList[id].push_back(ch);
		if(biDirEdge) adjList[ch].push_back(id);
	}
	vi getAdjacents(int id) {
		return adjList[id];
	}
	int getAdjacentAt(int id, int idx) {
		return adjList[id][idx];
	}
	int numAdj(int id) {
		return adjList[id].size();
	}
	virtual int numVertex() {
		return sz(adjList);
	}

	const vector<vi>& getAdjacentList() const {
		return adjList;
	}
};

#endif /* ADJ_LIST_GRAPH_H_ */
