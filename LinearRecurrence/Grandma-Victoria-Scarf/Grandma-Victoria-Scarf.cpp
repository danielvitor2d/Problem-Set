/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Grandma Victoria Scarf
	Link: https://www.urionlinejudge.com.br/judge/en/problems/view/2439
	Origin: OBI 2013 - Phase 2 - Level 2
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
const int mod = 1e9+7;

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

/*
|DP[N][0]|   |2 2|   |DP[N-1][0]|
|DP[N][1]| = |2 3| * |DP[N-1][1]|

|R(N)| = |1 1|   |DP[N][0]|   |2 2| ^ (N - 1) |DP[1][0] = 6|
               * |DP[N][1]| = |2 3| *         |Dp[1][1] = 6|
*/

i64 n;

int main() {
	fastIO();
	cin >> n;

	M base;
	base[0][0] = 2LL; base[0][1] = 2LL;
	base[1][0] = 2LL; base[1][1] = 3LL;

	base = base.exp(n - 1);

	cout << ((6LL * base[0][0]) % mod + (6LL * base[0][1]) % mod + 
		     (6LL * base[1][0]) % mod + (6LL * base[1][1]) % mod) % mod << '\n';

	return 0;
}
