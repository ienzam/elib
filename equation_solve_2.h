#ifndef __equation_solve_2_h__
#define __equation_solve_2_h__

#include "template.h"

/**
 * AC CODE
 */

/**
 * Solves equation of the format
 * a1*x + b1*y = c1
 * a2*x + b2*y = c2
 */
struct EquationSolve2 {
	bool valid;
	double x, y;
	EquationSolve2(double a1, double b1, double c1,
		       double a2, double b2, double c2) {
		double D  = a1*b2 - a2*b1;
		if(abs(D) < EPS) {
			valid = false;
			return;
		}
		double Dx = c1*b2 - c2*b1;
		double Dy = a1*c2 - a2*c1;

		valid = true;
		x = Dx / D;
		y = Dy / D;
	}
	bool isValid() { return valid; }
	double getX() { return x; }
	double getY() { return y; }
	pair<double, double> getSolution() { return mp(x, y); }
};

#endif

