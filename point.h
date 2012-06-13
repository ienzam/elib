//============================================================================
// Name        : point.h
// Author      : enzam
// Created At  : Jun 7, 2012 5:07:46 PM
// Description : None
// Accepted	   : Unknown
//============================================================================

#ifndef POINT_H_
#define POINT_H_

#include "template.h"

struct Point {
	double x, y;
	Point() :x(0), y(0) {}
	Point(double x, double y) : x(x), y(y) {}
	static Point invalidPoint() {
		return Point(
				numeric_limits<double>::infinity(),
				numeric_limits<double>::infinity()
				);
	}
	bool isValid() {
		return
				(x != numeric_limits<double>::infinity()) &&
				(y != numeric_limits<double>::infinity());
	}

	double sqrdis(const Point& b) {
		return sqr(x - b.x) + sqr(y - b.y);
	}

	double dis(const Point& b) {
		return sqrt(sqrdis(b));
	}

	void translate(double tx, double ty) {
		if(isValid()) { x += tx; y += ty; }
	}

	friend ostream& operator<<(ostream& out, const Point& p) {
		return out << '(' << p.x << ',' << p.y << ')';
	}

};

#endif /* POINT_H_ */
