/*
 * graph.h
 *
 *  Created on: Jun 2, 2012
 *      Author: enzam
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "template.h"

class Graph {
public:
	virtual int numVertex() = 0;
	virtual void addEdge(int id, int ch, bool biDirEdge = false) = 0;
	virtual vi getAdjacents(int id) = 0;
	virtual int getAdjacentAt(int id, int idx) = 0;
	virtual int numAdj(int id) = 0;
	virtual const vector<vi>& getAdjacentList() const = 0;
//	~Graph();
};


#endif /* GRAPH_H_ */
