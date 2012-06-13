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

struct Polygon {
	vector<Point> corners;
	Polygon() {}
	Polygon(const vector<Point>& pts) : corners(pts) {}
	void addCorner(const Point &pt) { corners.push_back(pt); }
	double getArea() {
		double res = 0;
		FOR(i, sz(corners))
		{
			Point
				p1 = i ? corners[i-1] : corners.back(),
				p2 = corners[i];
			res += (p1.x - p2.x) * (p1.y + p2.y);
		}
		return fabs(res) / 2;
	}
};

#endif /* POLYGON_H_ */
