#include <bits/stdc++.h>
using namespace std;

typedef long long int i64;

const int mod = 1e9+7;
const int D = 15;

int d;
i64 md;

struct M {
	i64 m[D][D];

	i64* operator[] (int i) {
		return m[i];
	}

	M operator*(M oth) {
		M res;
		for (int i = 0; i < d; ++i) {
			for (int j = 0; j < d; ++j) {
				res[i][j] = 0;
				for (int k = 0; k < d; ++k) {
					res[i][j] = (res[i][j] + m[i][k] * oth[k][j] % md + md) % md;
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

int n;
i64 ans, v[16];

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	while (cin >> d >> n >> md and d) {

		M base;
		for (int i = 0; i < d; ++i) {
			for (int j = 0; j < d; ++j) {
				if (i==j+1) base[i][j] = 1;
				else base[i][j] = 0;
			}
		}

		for (int i = 0; i < d; ++i) {
			cin >> base[0][i];
		}

		for(int i = 1; i <= d; ++i) {
			cin >> v[i];
		}

		if (n <= d) {
			cout << v[n] << '\n';
			continue;
		}

		base = base.exp(n - d);

		ans = 0LL;

		for (int i = 0; i < d; ++i) {
			ans = (ans + (base[0][i] * 1LL * v[d-i]) % md) % md;
		}

		cout << ans << '\n';
	}

	return 0;
}