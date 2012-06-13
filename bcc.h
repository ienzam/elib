//============================================================================
// Name        : bcc.h
// Author      : enzam
// Created At  : Jun 8, 2012 10:42:44 PM
// Description : Biconnected components, articulation points, bridges
// Accepted	   : YES, uva - 10199 - Tourist Guide
//============================================================================

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
	vi compId;
	vector<vi> compVertices;

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
				if(low[ch] == dfsnum[ch]) bridges.push_back(mp(now, ch));
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
			while(true) {
				int sTop = st.back(); st.pop_back();
				compId[sTop] = sz(compVertices) - 1;
				compVertices.back().push_back(sTop);
				if(sTop == now) break;
			}
		}
	}

public:
	void findBCCs() {
		if(!inGraph) {
			cerr << __PRETTY_FUNCTION__ << ": Y U NO SET THE INPUT GRAPH!" << endl;
			return;
		}

		visCount = 0;
		dfsnum.resize(inGraph->numVertex(), 0);
		low.resize(inGraph->numVertex());
		compId.resize(inGraph->numVertex());
		compVertices.clear();
		st.clear();
		artiPoints.clear();
		bridges.clear();

		FOR(i, inGraph->numVertex()) {
			if(!dfsnum[i]) dfs(i, -1);
		}
	}
	BCC() {}
	BCC(AdjListGraph& graph) : inGraph(&graph) {
		findBCCs();
	}

	/**
	 * Set the input graph to graph
	 */
	void setGraph(AdjListGraph& graph) { inGraph = &graph; }

	const vi& getArticulatioPoints() {
		return artiPoints;
	}
};

#endif /* BCC_H_ */
