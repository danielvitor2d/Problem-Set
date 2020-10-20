#include <bits/stdc++.h>
using namespace std;
using i64 = long long int;

const int D = 2;

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
					res[i][j] = res[i][j] + m[i][k] * oth[k][j];
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

i64 p, q, n;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	while (cin >> p >> q and (p or q)) {
		cin >> n;
		M base;
		base[0][0] = p; base[0][1] = -1;
		base[1][0] = q; base[1][1] = 0;
		base = base.exp(n);	
		cout << 2*base[0][0] + p*base[0][1] << '\n';
	}

	return 0;
}