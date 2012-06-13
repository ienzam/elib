#ifndef __CT3P__
#define __CT3P__

/**
 * AC CODE
 */

#include "template.h"
#include "equation_solve_2.h"
#include "point.h"
#include "circle.h"

/**
 * Takes three points and returns the circle
 * If three points in one line, then valid = false
 */
struct CircleThrough3Points { 
	bool valid;
	Circle c;
	CircleThrough3Points(Point p1, Point p2, Point p3) {
		double a1 = 2 * (p1.x - p2.x);
		double b1 = 2 * (p1.y - p2.y);
		double c1 = sqr(p1.x) + sqr(p1.y) - sqr(p2.x) - sqr(p2.y);

		double a2 = 2 * (p2.x - p3.x);
		double b2 = 2 * (p2.y - p3.y);
		double c2 = sqr(p2.x) + sqr(p2.y) - sqr(p3.x) - sqr(p3.y);
		DIM( solve , EquationSolve2(a1, b1, c1, a2, b2, c2) );
		valid = solve.isValid();
		if(!valid) return;
		c.x = solve.x;
		c.y = solve.y;
		c.r = sqrt( sqr(c.x - p1.x) + sqr(c.y - p1.y) );
	}
	bool isValid() { return valid; }
	Circle getCircle() { return c; }
};

#endif
