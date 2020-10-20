/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Tribonacc
	Link: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=0&problem=3914&mosmsg=Submission+received+with+ID+25636211
	Origin: Unknown
*/
#include <bits/stdc++.h>
using namespace std;
using i64 = long long int;

const i64 mod = 1e9+9;
const int D = 3;

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
					res[i][j] = (res[i][j] + (m[i][k] * oth[k][j]) % mod) % mod;
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

i64 n;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	
	while (cin >> n and n) {
		if (n <= 3) {
			cout << n-1 << '\n';
			continue;
		}
		M base;
		base[0][0] = 1LL; base[0][1] = 1LL; base[0][2] = 1LL;
		base[1][0] = 1LL; base[1][1] = 0LL; base[1][2] = 0LL;
		base[2][0] = 0LL; base[2][1] = 1LL; base[2][2] = 0LL;
		base = base.exp(n-3);
		cout << ((2LL * base[0][0]) % mod + (1LL * base[0][1]) % mod) % mod << '\n';
	}


	return 0;
}
