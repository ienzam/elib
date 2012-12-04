//============================================================================
// Name        : mcmf.h
// Author      : enzam
// Created At  : Jul 24, 2012 7:49:49 AM
// Description : None
// Accepted	   : Unknown
//============================================================================


#ifndef MCMF_H_
#define MCMF_H_

#include "template.h"

//cost type and max edge
template<class ctype, size_t MAXN>
struct MCMF {
    ctype INF;
    struct Edge { int x, y; ctype cap, cost; };
    vector<Edge> E;
    vector<int> adj[MAXN];
    int N, prev[MAXN];
    ctype dist[MAXN];

    MCMF() { INF = numeric_limits<ctype>::max(); }

    void init(int n) {
    	N = n;
    	E.clear();
    	FOR(i, N) adj[i].clear();
    }

    void add(int x, int y, ctype cap, ctype cost) {
        Edge e1={x,y,cap,cost}; adj[e1.x].push_back(E.size()); E.push_back(e1);
        Edge e2={y,x,0,-cost}; adj[e2.x].push_back(E.size()); E.push_back(e2);
    }

    /**
     * Returns (flowval, flowcost)
     */
    pair<ctype, ctype> mcmf(int s, int t) {
        int x;
        ctype flowVal = 0, flowCost = 0;
        while (true) {
            for (x = 0; x < N; x++) prev[x] = -1;
            for (x = 0; x < N; x++) dist[x] = INF;
            dist[s] = prev[s] = 0;

            for (x = 1; x;) {
                x = 0;
                Edge *begin = &E[0], *end = &E[E.size()];
                for (Edge *e = begin; e < end; ++e) {
                    if (e->cap > 0 && prev[e->x] != -1 && dist[e->x] + e->cost < dist[e->y]) {
                        dist[e->y] = dist[e->x] + e->cost;
                        prev[e->y] = e - begin;
                        x = 1;
                    }
                }
            }
            if (prev[t] == -1) break;

            ctype z = INF;
            for (x = t; x != s; x = E[prev[x]].x)
                z = min(z, E[prev[x]].cap);
            for (x = t; x != s; x = E[prev[x]].x)
                { E[prev[x]].cap -= z; E[prev[x]^1].cap += z; }
            flowVal += z; flowCost += z * dist[t];
        }
        return mp(flowVal, flowCost);
    }
};
#endif /* MCMF_H_ */
