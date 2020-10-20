/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: How Many Recursive Calls
	Link: https://www.urionlinejudge.com.br/judge/pt/problems/view/1033
	Origin: Unknown
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long int i64;

const int D = 3;

i64 mod;

struct M {
	i64 m[D][D];

	i64* operator[](int i) {
		return m[i];
	}

	M operator*(M oth) {
		M res;
		for (int i = 0; i < D; ++i) {
			for (int j = 0; j < D; ++j) {
				res[i][j] = 0;
				for (int k = 0; k < D; ++k) {
					res[i][j] = (res[i][j] + m[i][k] * oth[k][j] % mod + mod) % mod;
				}
			}
		}
		return res;
	}	

	M exp(i64 e) {
		M res;
		for (int i = 0; i < D; ++i)
			for (int j = 0; j < D; ++j)
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

int tc;
i64 n;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	while (cin >> n >> mod and (n or mod)) {
		cout << "Case " << ++tc << ':' << ' ' << n << ' ' << mod << ' ';
		M base;
		base[0][0] = 1; base[0][1] = 1; base[0][2] = 1;
		base[1][0] = 1; base[1][1] = 0; base[1][2] = 0;
		base[2][0] = 0; base[2][1] = 0; base[2][2] = 1;
		base = base.exp(n-1);
		cout << (base[0][0] + base[0][1] + base[0][2]) % mod << '\n';
	}


	return 0;
}