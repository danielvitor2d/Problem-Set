/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Recursive Sequence
	Link: https://www.spoj.com/problems/SEQ/
	Origin: Unknown
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
typedef pair<int, int> ii;
typedef pair<i64, i64> ll;
typedef vector<int> vi;
typedef vector<i64> vi64;
typedef vector<ii> vii;
typedef vector<ll> vll;
typedef vector<vi> vvi;

const double eps = 1e-9;

#define eq(a, b) (abs(a - b) < eps)
#define lt(a, b) ((a + eps) < b)
#define gt(a, b) (a > (b + eps))
#define le(a, b) (a < (b + eps))
#define ge(a, b) ((a + eps) > b)

#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define ms(a, x) memset(a, x, sizeof(a))
#define len(x) (x).size()
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

const int dtx[] = { 0, 0, -1, 1, 1, -1,  1, -1};
const int dty[] = {-1, 1,  0, 0, 1, -1, -1,  1};
const int dtxc[] = {1,  1, 2,  2, -1, -1, -2, -2};
const int dtyc[] = {2, -2, 1, -1,  2, -2,  1, -1};

const double pi = acos(-1.0);
const int inf = 0x3f3f3f3f;
const int maxn = 1e5+5;
const int mod = 1e9;

const int D = 10;

int k;

struct M {
	i64 m[D][D];
	
	i64* operator[](int i) {
		return m[i];
	}

	M operator-(M oth) {
		M res;
		for (int i = 0; i < d; ++i) {
			for (int j = 0; j < d; ++j) {
				res[i][j] = m[i][j] - oth[i][j];
			}
		}
		return res;
	}

	M operator+(M oth) {
		M res;
		for (int i = 0; i < d; ++i) {
			for (int j = 0; j < d; ++j) {
				res[i][j] = m[i][j] + oth[i][j];
			}
		}
		return res;
	}

	M operator*(M oth) {
		M res;
		for (int i = 0; i < d; ++i) {
			for (int j = 0; j < d; ++j) {
				res[i][j] = 0;
				for (int k = 0; k < d; ++k) {
					res[i][j] = (res[i][j] + m[i][k] * oth[k][j] % mod + mod) % mod;
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
			if (e & 1) res = res * base;
			base = base * base;
			e >>= 1LL;
		}
		return res;
	}
};

i64 b[11], c[11];
int tc, ans;
int n;

int main() {
	fastIO();
	
	cin >> tc;

	while (tc--) {
		cin >> k;
		for (int i = 1; i <= k; ++i) cin >> b[i];
		for (int i = 1; i <= k; ++i) cin >> c[i];
		cin >> n;

		if (n <= k) {
			cout << b[n] << '\n';
			continue;
		}

		M base;

		for (int i = 1; i <= k; ++i) {
			base[0][i-1] = c[i];
		}

		for (int i = 1; i < k; ++i) {
			for (int j = 0; j < k; ++j) {
				base[i][j] = (i == j + 1);
			}
		}

		M R = base.exp(n - k);

		ans = 0;
		for (int i = 0; i < k; ++i) {
			ans = (ans + R[0][i] * b[k - i]) % mod;
		}

		cout << ans << '\n';
	}

	return 0;
}
