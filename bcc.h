//============================================================================
// Name        : bcc.h
// Author      : enzam
// Created At  : Jun 8, 2012 10:42:44 PM
// Description : Biconnected components, articulation points, bridges
// Accepted	   : YES, uva - 10199 - Tourist Guide
//============================================================================

/** Usage:
 * First set the graph in constructor or by calling setGraph().
 * Then call findBCCs() [optional, but if you change the graph
 * after setGraph , then you need to call it explicitly]
 * Then use the methods -
 * const vi& getArticulationPoints()
 * const vector<vi>& getBiConnectedComponents()
 * const vector<pii>& getBridges()
 */

#ifndef BCC_H_
#define BCC_H_

#include "template.h"
#include "adj_list_graph.h"

struct BCC {
private:
	AdjListGraph *inGraph;
	vi dfsnum;
	vi low;
	int visCount;
	vi st;

	vector<pii> bridges;
	vi artiPoints;
//	vi compId;
	vector<vi> compVertices;

	bool foundBCCs;

	void dfs(int now, int parent) {
		low[now] = dfsnum[now] = ++visCount;
		st.push_back(now);
		bool isArti = false;
		int visChildCount = 0;
		RDIM(adjList, inGraph->getAdjacentList());
		FORstl(i, adjList[now]) { int ch = *i;
			if(ch == parent) continue;
			if(dfsnum[ch]) {
				amin(low[now], dfsnum[ch]);
			} else {
				visChildCount++;
				dfs(ch, now);
				amin(low[now], low[ch]);
				if(dfsnum[now] <= low[ch]) isArti = true;
				if(dfsnum[ch] == low[ch]) bridges.push_back(mp(now, ch));
			}
		}
		if(parent == -1) {
			isArti = (visChildCount >= 2);
		}
		if(isArti) {
			artiPoints.push_back(now);
		}

		if(low[now] == dfsnum[now]) {
			compVertices.push_back(vi());
			int sTop;
			do {
				sTop = st.back(); st.pop_back();
//				compId[sTop] = sz(compVertices) - 1;
				compVertices.back().push_back(sTop);
			} while(sTop != now);
		}
	}

public:
	void findBCCs() {
		if(!inGraph) {
			cerr << __PRETTY_FUNCTION__ << ": Y U NO SET THE INPUT GRAPH!" << endl;
			return;
		}

		visCount = 0;
		fill(all(dfsnum), 0);
		dfsnum.resize(inGraph->numVertex(), 0);
		low.resize(inGraph->numVertex());
//		compId.resize(inGraph->numVertex());
		compVertices.clear();
		st.clear();
		artiPoints.clear();
		bridges.clear();

		FOR(i, inGraph->numVertex()) {
			if(!dfsnum[i]) dfs(i, -1);
		}

		foundBCCs = true;
	}

	BCC() : foundBCCs(false) {}
	BCC(AdjListGraph& graph) : inGraph(&graph), foundBCCs(false) {
		//findBCCs();
	}

	/**
	 * Set the input graph to graph
	 */
	void setGraph(AdjListGraph& graph) { inGraph = &graph; foundBCCs = false; }

	const vi& getArticulationPoints() {
		if(!foundBCCs) findBCCs();
		return artiPoints;
	}

	const vector<vi>& getBiConnectedComponents() {
		if(!foundBCCs) findBCCs();
		return compVertices;
	}

	const vector<pii>& getBridges() {
		if(!foundBCCs) findBCCs();
		return bridges;
	}
};

#endif /* BCC_H_ */
