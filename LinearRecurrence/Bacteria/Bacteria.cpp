/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Bacteria
	Link: https://www.urionlinejudge.com.br/judge/pt/problems/view/1422
	Origin: XIII IME-USP 2009 Programming Marathon.
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long int i64;

const i64 mod = 13371337LL;
const int D = 5;

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

i64 n;
i64 a, b, c, d, sum;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	
	while (cin >> n and n) {
		cin >> a >> b >> c >> d;
		sum = a+b+c+d;
		M base;
		base[0][0] = 2LL; base[0][1] = 0LL; base[0][2] = 0LL; base[0][3] = 0LL; base[0][4] = -1LL;
		base[1][0] = 1LL; base[1][1] = 0LL; base[1][2] = 0LL; base[1][3] = 0LL; base[1][4] =  0LL;
		base[2][0] = 0LL; base[2][1] = 1LL; base[2][2] = 0LL; base[2][3] = 0LL; base[2][4] =  0LL;
		base[3][0] = 0LL; base[3][1] = 0LL; base[3][2] = 1LL; base[3][3] = 0LL; base[3][4] =  0LL;
		base[4][0] = 0LL; base[4][1] = 0LL; base[4][2] = 0LL; base[4][3] = 1LL; base[4][4] =  0LL;
		base = base.exp(n-4LL);
		cout << (((sum * base[0][0]) % mod + (d * base[0][1]) % mod + (c * base[0][2]) % mod + (b * base[0][3]) % mod + (a * base[0][4]) % mod) % mod + mod) % mod << '\n';
	}

	return 0;
}
