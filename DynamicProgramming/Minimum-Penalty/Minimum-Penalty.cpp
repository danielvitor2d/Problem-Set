/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Minimum Penalty
	Link: https://www.urionlinejudge.com.br/judge/en/problems/view/2319
	Origin: OBI 2006 - Second Phase - Level 2
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
const int maxn = 1e3+5;
const int mod = 1e9+7;

int f(int x, int b) {
	int rs = 0;
	while (x % b == 0) { ++rs; x /= b; }
	return rs;
}

int n, gr[maxn][maxn];
int dp[maxn][maxn];

int call(int x) {
	dp[0][0] = f(gr[0][0], x);

	for (int i = 1; i < n; ++i) {
		dp[0][i] = (gr[0][i] > 0 ? dp[0][i-1] + f(gr[0][i], x) : inf);
		dp[i][0] = (gr[i][0] > 0 ? dp[i-1][0] + f(gr[i][0], x) : inf);
	}

	for (int i = 1; i < n; ++i) {
		for (int j = 1; j < n; ++j) {
			dp[i][j] = (gr[i][j] > 0 ? f(gr[i][j], x) + min(dp[i-1][j], dp[i][j-1]) : inf);
		}
	}

	return dp[n-1][n-1];
}

int main() {
	fastIO();

	cin >> n;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> gr[i][j];
		}
	}

	cout << min(call(2), call(5)) << '\n';

	return 0;
}