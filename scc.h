//============================================================================
// Name        : scc.h
// Author      : enzam
// Created At  : Jun 2, 2012
// Description : Strongly Connected Component with Kosaraju's algorithm
// Accepted	   : YES, uva - 10731 - Test
//============================================================================

#ifndef SCC_H_
#define SCC_H_

#include "template.h"
#include "adj_list_graph.h"

struct SCCKosaraju {
private:
	AdjListGraph *inGraph;
	AdjListGraph *revGraph;
	AdjListGraph *sccGraph;
	vector<vi> compVertices;
	vi compId;
	stack<int> st;
	vector<bool> vis;
	void dfs1(int now) {
		if(vis[now]) return;
		vis[now] = true;

		RDIM(adjList, inGraph->getAdjacentList());
		FORstl(i, adjList[now]) {
			dfs1(*i);
		}

		st.push(now);
	}

	void dfs2(int now) {
		if(compId[now] != -1) return;
		compId[now] = sz(compVertices) - 1;
		compVertices.back().push_back(now);
		RDIM(adjList, revGraph->getAdjacentList());
		FORstl(i, adjList[now]) {
			dfs2(*i);
		}
	}
public:
	SCCKosaraju() : inGraph(0), sccGraph(0) { }
	SCCKosaraju (AdjListGraph& graph)
	 : inGraph(&graph), sccGraph(0) {
		findSCCs();
	}

	void findSCCs() {
		if(!inGraph) {
			cerr << __PRETTY_FUNCTION__ << ": Y U NO SET THE INPUT GRAPH!" << endl;
			return;
		}

		RDIM(adjList, inGraph->getAdjacentList());

		revGraph = new AdjListGraph(inGraph->numVertex());
		FOR(i, inGraph->numVertex()) {
			FORstl(j, adjList[i]) {
				revGraph->addEdge(*j, i);
			}
		}

		vis.assign(inGraph->numVertex(), false);
		FOR(i, inGraph->numVertex()) { dfs1(i); }

		compId.assign(inGraph->numVertex(), -1);
		while(st.size()) {
			int now = st.top(); st.pop();
			if(compId[now] != -1) continue;
			compVertices.push_back(vi());
			dfs2(now);
		}
		delete revGraph;

		if(sccGraph) delete sccGraph;
		sccGraph = new AdjListGraph(compVertices.size());
		FOR(i, inGraph->numVertex()) {
			FORstl(j, adjList[i]) {
				if(compId[i] != compId[*j])
				sccGraph->addEdge(compId[i], compId[*j]);
			}
		}
	}

	~SCCKosaraju() {
		if(sccGraph) delete sccGraph;
	}

	/**
	 * Set the input graph to graph
	 */
	void setGraph(AdjListGraph& graph) { inGraph = &graph; }

	/**
	 * Returns the input graph
	 */
	Graph& G() { return *inGraph; }

	/**
	 * Returns the const reference of the scc graph
	 */
	const Graph& getSCCGraph() { return *sccGraph; }

	/**
	 * Returns the const reference of the scc graph, same as getSCCGraph()
	 */
	const Graph& SCCG() { return *sccGraph; }

	/**
	 * Returns the list of vertices belongs to a component
	 */
	const vector<vi>& getCompontentVertices() {
		return compVertices;
	}

	/**
	 * Returns the component id of the vertices
	 */
	const vi& getVertexCompIds() {
		return compId;
	}
};

#endif /* SCC_H_ */
