//============================================================================
// Name        : dynamic_DMatrix.h
// Author      : enzam
// Created At  : Nov 3, 2012 3:28:10 PM
// Description : None
// Accepted	   : Unknown
//============================================================================


#ifndef DYNAMIC_MATRIX_H_
#define DYNAMIC_MATRIX_H_

#include "template.h"

template<class vtype>
struct DMatrix {
	vector< vector<vtype> > val;
	int row, col;

	int numRows() const { return row; }
	int numColumns() const { return col; }

	DMatrix(int row, int col, bool makeIdentity = false) : row(row), col(col) {
		val = vector< vector<vtype> >(row, vector<vtype>(col));
		FOR(i, row) FOR(j, col) {
			val[i][j] = 0;
			if(i == j && makeIdentity == 1) val[i][j] = 1;
		}
	}

	vtype& operator()(int a, int b) { return val[a][b]; }
	vtype operator()(int a, int b) const { return val[a][b]; }

//	void powerUp(ll pow) {
//		assert(row == col);
//		int D = row;
//		if(!pow) {
//			FOR(i, row) FOR(j, col) { val[i][j] = 0; if(i == j) val[i][j] = 1; }
//			return;
//		}
//		DMatrix<t> ans = A^(pow/2); ans = ans * ans;
//		if(pow & 1) ans = ans * A;
//		return ans;
//	}

};

template<class t>
DMatrix<t> operator*(DMatrix<t> &A, DMatrix<t> &B) {
	assert(A.col == B.row);
	int I = A.row, K = A.col, J = B.col;
	DMatrix<t> C(I, J);
	FOR(i, I) FOR(j, J) FOR(k, K) {
		C(i,j) += A(i,k) * B(k,j);
	}
	return C;
}

template<class t>
DMatrix<t> operator^(DMatrix<t> &A, ll pow) {
	assert(A.row == A.col);
	int D = A.row;
	if(!pow) {
		return DMatrix<t>(D, D, true);
	}
	DMatrix<t> ans = A^(pow/2); ans = ans * ans;
	if(pow & 1) ans = ans * A;
	return ans;
}

template<class t>
ostream& operator<<(ostream& out, const DMatrix<t>& mat) {
	FOR(i, mat.numRows()) {
		out << "|";
		FOR(j, mat.numColumns()) {
			out.width(4);
			out << mat(i, j);
		}
		out << "|";
		out << endl;
	}
	return out;
}

#endif /* DYNAMIC_MATRIX_H_ */
