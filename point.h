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

template<class Type>
struct TPoint {
	Type x, y;
	TPoint() :x(0), y(0) {}
	TPoint(Type x, Type y) : x(x), y(y) {}
	TPoint<Type>(const TPoint<Type>& p) { x = p.x, y = p.y; }
	static TPoint invalidPoint() {
		return Point(
				numeric_limits<Type>::infinity(),
				numeric_limits<Type>::infinity()
				);
	}
	bool isValid() {
		return
				(x != numeric_limits<Type>::infinity()) &&
				(y != numeric_limits<Type>::infinity());
	}

	Type sqrdis(const TPoint& b) {
		return sqr(x - b.x) + sqr(y - b.y);
	}

	double dis(const TPoint& b) {
		return sqrt(sqrdis(b));
	}

	void translate(Type tx, Type ty) {
		if(isValid()) { x += tx; y += ty; }
	}

	friend ostream& operator<<(ostream& out, const TPoint& p) {
		return out << '(' << p.x << ',' << p.y << ')';
	}

	friend istream& operator>>(istream& in, TPoint& p) {
		return in >> p.x >> p.y;
	}

	bool operator <(const TPoint<Type> &p) const {
        if(y != p.y) return y < p.y;
        return x < p.x;
    }
};

typedef TPoint<double> PointD;
typedef TPoint<int> PointI;
typedef TPoint<ll> PointLL;

#endif /* POINT_H_ */
