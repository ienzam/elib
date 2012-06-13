//============================================================================
// Name        : line.h
// Author      : enzam
// Created At  : Jun 7, 2012 5:42:20 PM
// Description : None
// Accepted	   : Unknown
//============================================================================

#ifndef LINE_H_
#define LINE_H_

#include "template.h"

struct Line {
	double a, b, c;

	Line(double a, double b, double c) : a(a), b(b), c(c) {}

	void translate(double tx, double ty) {
		//if(isValid()) { x += tx; y += ty; }
		c += tx * a + ty * b;
	}
};

#endif /* LINE_H_ */
