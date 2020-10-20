#include <bits/stdc++.h>
using namespace std;
using i64 = long long int;

const int D = 2;

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
					res[i][j] = (res[i][j] + m[i][k] * oth[k][j] & (mod - 1) + mod) & (mod - 1);
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

i64 n, m;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	while (cin >> n >> m) {
		mod = (1LL << m);
		if (n <= 1) {
			cout << (n & (mod - 1)) << '\n';
			continue;
		}
		M base;
		base[0][0] = 1; base[0][1] = 1;
		base[1][0] = 1; base[1][1] = 0;
		cout << base.exp(n - 1)[0][0] << '\n';
	}

	return 0;
}