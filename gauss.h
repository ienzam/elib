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

template<class T>
struct GaussEquationSolver {
	int nUnknown;
	vector<vector<T> > equations;
	GaussEquationSolver(int nUnknown) : nUnknown(nUnknown) {}
	void addEquation(const vector<T>& equation) {
		assert(sz(equation) == nUnknown + 1);
		equations.push_back(equation);
	}

	void addEquation(T equation[]) {
		equations.push_back(vector<T>(equation, equation + nUnknown + 1));
	}

	void solve() {
		int nEq = sz(equations);
		int loop = min(nUnknown, nEq);
		FOR(ref, loop) {
			int k = ref;
			FORab(j, ref + 1, nEq - 1) {
				if(abs(equations[k][ref]) < abs(equations[j][ref])) k = j;
			}
			equations[k].swap(equations[ref]);

			if(equations[ref][ref] == 0) {
				//TODO: check if equations[ref][ref] == 0
				continue;
				int k = ref;
				FORab(j, ref + 1, nUnknown) {
					if(abs(equations[ref][k]) < abs(equations[ref][j])) k = j;
				}
				FOR(i, sz(equations)) {
					swap(equations[i][k], equations[i][ref]);
				}
				if(equations[ref][ref] == 0) return;
			}

			FORab(i, ref + 1, nUnknown) equations[ref][i] /= equations[ref][ref];
			equations[ref][ref] = 1;

			FOR(j, nEq) {
				if(j == ref) continue;
				RDIM( t , equations[j][ref] );
//				if( EQ(t, 0) ) continue;
				if(t == 0) continue;
				FORab(i, ref + 1, nUnknown) {
					equations[j][i] -= equations[ref][i] * t;
				}
				t = 0;
			}
		}
	}
};

#endif /* GAUSS_H_ */
