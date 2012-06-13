#ifndef MODINT_H_
#define MODINT_H_

#include "template.h"

extern const int MOD;
struct ModInt {
	int v;
	ModInt(int a = 0) : v ( ( (a % MOD) + MOD ) % MOD ) {}
};
ModInt operator-(ModInt a) { return -a.v; }
bool operator==(ModInt a, ModInt b) { return a.v == b.v;}
ModInt operator+(ModInt a, ModInt b) { return a.v+b.v; }
ModInt operator-(ModInt a, ModInt b) { return a.v-b.v; }
ModInt operator*(ModInt a, ModInt b) { return a.v*b.v; }

ModInt& operator+=(ModInt &a, ModInt b) { return a = a + b; }
ModInt& operator-=(ModInt &a, ModInt b) { return a = a - b; }
ModInt& operator*=(ModInt &a, ModInt b) { return a = a * b; }

ModInt operator^(ModInt n, ModInt p) {
	if(!p.v) return 1;
	ModInt ans = n^(p.v/2); ans = ans*ans;
	if(p.v & 1) ans = ans * n;
	return ans;
}
ModInt operator/(ModInt a, ModInt b) { return a.v*(b^(MOD-2)); }
ostream& operator<<(ostream& out, ModInt a) { return out << a.v; }
istream& operator>>(istream& in, ModInt& a) {
	int v; in >> v;
	a = ModInt(v);
	return in;
}

#endif /* MODINT_H_ */
