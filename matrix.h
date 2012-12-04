//============================================================================
// Name        : matrix.h
// Author      : enzam
// Created At  : Oct 5, 2012 12:27:10 PM
// Description : None
// Accepted	   : Unknown
//============================================================================


#ifndef MATRIX_H_
#define MATRIX_H_

#include "template.h"

template<class vtype, size_t row, size_t col>
struct Matrix {
	vtype val[row][col];

	Matrix() {
		FOR(i, row) FOR(j, col) val[i][j] = 0;
	}

	vtype& operator()(int a, int b) {
		return val[a][b];
	}

	vtype* operator[](int a) {
		return val[a];
	}

	template<class t, size_t I, size_t K, size_t J>
	friend Matrix<t,I,J> operator*(Matrix<t,I,K> &A, Matrix<t,K,J> &B) {
		Matrix<t,I,J> C;
		FOR(i, I) FOR(j, J) FOR(k, K) {
			C(i,j) += A(i,k) * B(k,j);
		}
		return C;
	}

	template<class t, size_t D>
	friend Matrix<t,D,D> operator^(Matrix<t,D,D> &A, ll pow) {
		if(!pow) {
			Matrix<t,D,D> ans;
			FOR(i, D) ans[i][i] = 1;
			return ans;
		}
		Matrix<t,D,D> ans = A^(pow/2); ans = ans * ans;
		if(pow & 1) ans = ans * A;
		return ans;
	}
};

template<size_t r, size_t c> struct MatrixI : Matrix<int,r,c> {};

#endif /* MATRIX_H_ */
