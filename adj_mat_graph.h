//NOT COMPLETED
//============================================================================
// Name        : adj_mat_graph.h
// Author      : enzam
// Created At  : Jul 24, 2012 7:28:52 AM
// Description : None
// Accepted	   : Unknown
//============================================================================


#ifndef ADJ_MAT_GRAPH_H_
#define ADJ_MAT_GRAPH_H_

#include "template.h"
#include "graph.h"

struct AdjMatrixGraph : public Graph {
	vector< vector<int> > adjMat;
	AdjMatrixGraph(int n = 0) {
		adjMat = vector< vector<int> >(n , vector<int>(n) );
	}

	void clear() { adjMat.clear(); }

	void addNode() {
		FOR(i, sz(adjMat)) adjMat[i].push_back(0);
		adjMat.push_back(vector<int>(sz(adjMat)+1));
	}

	void addEdge(int id, int ch, bool biDirEdge = false) {
		adjMat[id][ch] = 1;
		if(biDirEdge) adjMat[ch][id] = 1;
	}

	void addEdge(int id, int ch, int cost, bool biDirEdge = false) {
		adjMat[id][ch] = cost;
		if(biDirEdge) adjMat[ch][id] = cost;
	}

	vi getAdjacents(int id) {
		return adjMat[id];
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

#endif /* ADJ_MAT_GRAPH_H_ */
