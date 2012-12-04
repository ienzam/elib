//============================================================================
// Name        : polygon.h
// Author      : enzam
// Created At  : Jun 7, 2012 7:42:02 PM
// Description : None
// Accepted	   : Unknown
//============================================================================

#ifndef POLYGON_H_
#define POLYGON_H_

#include "template.h"

template<class Type>
struct Polygon {
	vector< TPoint<Type> > corners;
	Polygon() {}
	Polygon(const vector<TPoint<Type> >& pts) : corners(pts) {}
	void addCorner(const TPoint<Type> &pt) { corners.push_back(pt); }
	static double getArea(const vector< TPoint<Type> >& corners) {
		double res = 0;
		FOR(i, sz(corners))
		{
			TPoint<Type>
				p1 = i ? corners[i-1] : corners.back(),
				p2 = corners[i];
			res += (p1.x - p2.x) * (p1.y + p2.y);
		}
		return fabs(res) / 2;
	}
	double getArea() { return getArea(corners); }
};

#endif /* POLYGON_H_ */
