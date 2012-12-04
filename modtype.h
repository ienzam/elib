//============================================================================
// Name        : modtype.h
// Author      : enzam
// Created At  : Nov 3, 2012 3:13:57 PM
// Description : None
// Accepted	   : Unknown
//============================================================================


#ifndef MODTYPE_H_
#define MODTYPE_H_

#include "template.h"

template<class T, T MOD>
struct ModT {
	T v;
	ModT(T a = 0) {
		if(a <= -MOD || a >= MOD) a %= MOD;
		if(a < 0) { a += MOD; }
		v = a;
	}
	ModT(const ModT& a) { v = a.v; }
//	ModT& operator=(T a) { return v = a; }

	friend ModT operator-(ModT a) { return -a.v; }
	friend bool operator==(ModT a, ModT b) { return a.v == b.v;}
	friend ModT operator+(ModT a, ModT b) { return a.v+b.v; }
	friend ModT operator-(ModT a, ModT b) { return a.v-b.v; }
	friend ModT operator*(ModT a, ModT b) { return a.v*b.v; }

	friend ModT& operator+=(ModT &a, ModT b) { return a = a + b; }
	friend ModT& operator-=(ModT &a, ModT b) { return a = a - b; }
	friend ModT& operator*=(ModT &a, ModT b) { return a = a * b; }

	friend ModT operator^(ModT n, ModT p) {
		if(!p.v) return 1;
		ModT ans = n^(p.v/2); ans = ans*ans;
		if(p.v & 1) ans = ans * n;
		return ans;
	}
	friend ModT operator/(ModT a, ModT b) { return a.v*(b^(MOD-2)); }
	friend ostream& operator<<(ostream& out, ModT a) { return out << a.v; }
	friend istream& operator>>(istream& in, ModT& a) {
		int v; in >> v;
		a = ModT(v);
		return in;
	}
};

template<int MOD> struct ModInt : ModT<int,MOD> { ModInt(int a = 0) : ModT<int,MOD>(a) {} };
template<ll MOD> struct ModLL : ModT<ll,MOD> {
	ModLL(ll a = 0) : ModT<ll,MOD>(a) {}
	ModLL(const ModT<ll,MOD>& a) : ModT<ll,MOD>(a) {}
};

#endif /* MODTYPE_H_ */
