//============================================================================
// Name        : circle.h
// Author      : enzam
// Created At  : Jun 7, 2012 5:08:12 PM
// Description : None
// Accepted	   : Unknown
//============================================================================

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "template.h"
#include "point.h"
#include "line.h"
#include "equation_solve_2.h"

class Circle {
private:
	bool valid;
public:
	double x, y, r;

	Circle() : x(0), y(0), r(0) {}
	Circle(const Point& p, double r) : x(p.x), y(p.y), r(r) {}
	Circle(double x, double y, double r) : x(x), y(y), r(r) {}

	static Circle from3Points(Point p1, Point p2, Point p3) {
		double a1 = 2 * (p1.x - p2.x);
		double b1 = 2 * (p1.y - p2.y);
		double c1 = sqr(p1.x) + sqr(p1.y) - sqr(p2.x) - sqr(p2.y);

		double a2 = 2 * (p2.x - p3.x);
		double b2 = 2 * (p2.y - p3.y);
		double c2 = sqr(p2.x) + sqr(p2.y) - sqr(p3.x) - sqr(p3.y);
		DIM( solve , EquationSolve2(a1, b1, c1, a2, b2, c2) );
		Circle c;
		if(solve.isValid()) {
			c.x = solve.x;
			c.y = solve.y;
			c.r = sqrt( sqr(c.x - p1.x) + sqr(c.y - p1.y) );
		} else {
			c.x = c.y = c.r = 0;
		}
		return c;
	}

	bool isValid() {
		return (!ZERO(r));
	}

	pair<Point, Point> getIntersection(Line l) {
		l.translate(-x, -y);
		double a = l.a, b = l.b, c = l.c;

		double x0 = -a*c/(a*a+b*b),  y0 = -b*c/(a*a+b*b);
		if (c*c > r*r*(a*a+b*b)+EPS)
			return mp(Point::invalidPoint(), Point::invalidPoint());
		else if (abs (c*c - r*r*(a*a+b*b)) < EPS) {
			return mp(Point(x0 + x, y0 + y), Point::invalidPoint());
		} else {
			double d = r*r - c*c/(a*a+b*b);
			double mult = sqrt (d / (a*a+b*b));
			double ax,ay,bx,by;
			ax = x0 + b * mult;
			bx = x0 - b * mult;
			ay = y0 - a * mult;
			by = y0 + a * mult;
			return mp(Point(ax + x, ay + y), Point(bx + x, by + y));
		}
	}

	void translate(double tx, double ty) {
		if(isValid()) { x += tx; y += ty; }
	}

	pair<Point, Point> getIntersection(const Circle& c) {
		Circle c1 = *this, c2 = c;
		c2.translate(-x, -y);
		c1.translate(-x, -y);

//		_(c1) _(c2);

		Line l(-2*c2.x, -2*c2.y, sqr(c2.x)+sqr(c2.y)+sqr(c1.r)-sqr(c2.r));
		DIM( ans , c1.getIntersection(l) );
		ans.first.translate(x, y);
		ans.second.translate(x, y);
		return ans;
	}

	friend ostream& operator<<(ostream& out, const Circle& c) {
		return out << '(' << c.x << ',' << c.y <<',' << c.r << ')';
	}

};

#endif /* CIRCLE_H_ */
