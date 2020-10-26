/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Letters
	Link: https://www.urionlinejudge.com.br/judge/pt/problems/view/1714
	Origin: SBC 2014 Programming Marathon
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
#define len(x) (int)(x).size()
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
const int maxn = 100+5;
const int mod = 1e9+7;

inline int get(char c) {
	if ('a' <= c and c <= 'j') return 0;
	return 1;
}

inline int to(char c) {
	if ('a' <= c and c <= 'j') return (c-'a');
	return c-'A';
}

int n, target;
char gr[maxn][maxn];
queue<ii> q;
vvi dist;

int solve(int i, int j) {
	q.emplace(i, j);

	dist = vvi(n, vi(n, inf));
	dist[i][j] = 0;

	while (!q.empty()) {
		ii u = q.front(); q.pop();
		for (int k = 0; k < 4; ++k) {
			int ni = u.fi + dtx[k], nj = u.se + dty[k];
			if (0 > ni or ni > n-1 or 0 > nj or nj > n-1 or dist[ni][nj] != inf) continue;
			if (((target >> to(gr[ni][nj])) & 1) == get(gr[ni][nj])) {
				dist[ni][nj] = dist[u.fi][u.se] + 1;
				q.emplace(ni, nj);
			}
		}
	}

	return dist[n-1][n-1];
}

int main() {
	fastIO();
	
	cin >> n;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> gr[i][j];
		}
	}

	int ans = inf;

	for (int mask = 0; mask < (1 << 10); ++mask) {
		target = mask;
		if (((target >> to(gr[0][0])) & 1) == get(gr[0][0])) {
			ans = min(ans, 1 + solve(0, 0));
		}
	}

	if (ans == inf) ans = -1;
	cout << ans << '\n';

	return 0;
}
