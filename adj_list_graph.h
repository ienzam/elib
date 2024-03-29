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
	AdjListGraph(int n = 0) {
		adjList = vector< vector<int> >(n);
	}

	AdjListGraph(const vector< vector<int> >& v) : adjList(v) {}

	void clear() { adjList.clear(); }

	void addNode() {
		adjList.push_back(vector<int>());
	}

	/**
	 * id = start, ch = end, biDirEdge = if bidirectional, default false
	 */
	void addEdge(int id, int ch, bool biDirEdge = false) {
		adjList[id].push_back(ch);
		if(biDirEdge) adjList[ch].push_back(id);
	}
	const vi& getAdjacents(int id) {
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
