/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long int i64;

const i64 mod = 98765431LL;
const int D = 2;

int d = D;

struct M {
	i64 m[D][D];

	i64* operator[](int i) {
		return m[i];
	}

	M operator*(M oth) {
		M res;
		for (int i = 0; i < d; ++i) {
			for (int j = 0; j < d; ++j) {
				res[i][j] = 0LL;
				for (int k = 0; k < d; ++k) {
					res[i][j] = (res[i][j] + (m[i][k] * oth[k][j]) % mod) % mod;
				}
			}
		}
		return res;
	}	

	M exp(i64 e) {
		M res;
		for (int i = 0; i < d; ++i)
			for (int j = 0; j < d; ++j)
				res[i][j] = (i==j);
		M base = *this;
		while (e > 0) {
			if (e & 1LL) res = res * base;
			base = base * base;
			e >>= 1LL;
		}
		return res;
	}
};

inline i64 modSum(i64 a, i64 b, i64 md = mod) {
	i64 ans = a + b;
	if (ans >= md) ans -= md;
	return ans;
}
inline i64 modMul(i64 a, i64 b, i64 md = mod) {
	return (a * b) % md;
}

const int maxn = 50500;

int n, t;
i64 sum_of_all, c[maxn];

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	cin >> n >> t;

	for (int i = 0; i < n; ++i) {
		cin >> c[i];
		sum_of_all += c[i];
	}

	M base;
	base[0][0] = 0LL; base[0][1] = n-1LL;
	base[1][0] = 1LL; base[1][1] = n-2LL;

	base = base.exp(t);

	i64 a = base[0][0], b = base[1][0];

	for (int i = 0; i < n; ++i) {
		cout << modSum(modMul(a, c[i]), modMul((sum_of_all - c[i]) % mod, b)) << '\n';
	}

	return 0;
}