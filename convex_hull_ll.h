//============================================================================
// Name        : convex_hull_ll.h
// Author      : enzam
// Created At  : Jul 29, 2012 6:06:58 PM
// Description : None
// Accepted	   : Unknown
//============================================================================


#ifndef CONVEX_HULL_LL_H_
#define CONVEX_HULL_LL_H_

#include "template.h"
#include "point.h"

struct ConvexHullLL {
	vector<PointLL> points;

	void clear() { points.clear(); }

	void addPoint(ll x, ll y) { points.push_back(PointLL(x, y)); }

	void addPoint(PointLL p) { points.push_back(p); }

	// 2D cross product.
	// Return a positive value, if OAB makes a counter-clockwise turn,
	// negative for clockwise turn, and zero if the points are collinear.
	static ll cross(const PointLL &O, const PointLL &A, const PointLL &B)
	{
	    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
	}

	// Returns a list of points on the convex hull in counter-clockwise order.
	// Note: the last PointLL in the returned list is the same as the first one.
	static vector<PointLL> getConvexHull(vector<PointLL>& P)
	{
	    int n = P.size(), k = 0;
	    vector<PointLL> H(2*n);

	    // Sort points lexicographically
	    sort(P.begin(), P.end());

	    // Build lower hull
	    for (int i = 0; i < n; i++) {
	        while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
	        H[k++] = P[i];
	    }

	    // Build upper hull
	    for (int i = n-2, t = k+1; i >= 0; i--) {
	        while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
	        H[k++] = P[i];
	    }

	    H.resize(k);
	    return H;
	}

	vector<PointLL> getConvexHull() { return getConvexHull(points); }

};

#endif /* CONVEX_HULL_LL_H_ */
