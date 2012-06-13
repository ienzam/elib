//============================================================================
// Name        : gauss.h
// Author      : enzam
// Created At  : Jun 12, 2012 1:16:10 PM
// Description : None
// Accepted	   : Unknown
//============================================================================

#ifndef GAUSS_H_
#define GAUSS_H_

#include "template.h"

struct EquationSolver {
	int nUnknown;
	vector<vi> equations;
	EquationSolver(int nUnknown) : nUnknown(nUnknown) {}
	void addEquation(const vi& equation) {
		assert(sz(equation) == nUnknown);
		equations.push_back(equation);
	}

	void addEquation(int equation[]) {
		equations.push_back(vi(equation, equation + nUnknown));
	}

	void solve() {
		int nEq = sz(equations);
		FOR(ref, nUnknown) {
			int k = ref;
			FORab(j, ref + 1, nEq - 1) {
				if(abs(equations[k][i]) < abs(equations[j][i])) k = j;
			}
			equations[k].swap(equations[ref]);
			//TODO: check if equations[ref][ref] == 0
			FORab(i, ref, nUnknown - 1) equations[ref][i] /= equations[ref][ref];
			FOR(j, nEq) {
				if(j == ref) continue;
				double t = equations[j][ref];
				if( EQ(t, 0) ) continue;
				FORab(i, ref, nUnknown - 1) {
					equations[j][i] -= equations[ref][i] * t;
				}
			}

		}
	}
};

#endif /* GAUSS_H_ */
