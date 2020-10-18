/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Water Crisis
	Link: https://www.urionlinejudge.com.br/judge/en/problems/view/2789
	Origin: Mining Marathon 2018
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
const int maxn = 5e3+5;
const int mod = 1e9+7;
const int L = 20;

i64 dp[maxn];

int n, m, d, q;
int a, b, w;
vi gr[maxn];

i64 v[maxn];
int c[maxn];

int in[maxn], out[maxn], timer;
int anc[maxn][L];

void dfs(int u, int p) {
	in[u] = ++timer;
	anc[u][0] = p;
	for (int i = 1; i < L; ++i) anc[u][i] = anc[ anc[u][i-1] ][i-1];
	for (int to : gr[u]) if (to != p) dfs(to, u);
	out[u] = ++timer;
}

bool is_anc(int u, int v) {
	return in[u] <= in[v] and out[v] <= out[u];
}

int lca(int u, int v) {
	if (is_anc(u, v)) return u;
	if (is_anc(v, u)) return v;
	for (int i = L-1; i >= 0; --i)
		if (!is_anc(anc[u][i], v)) u = anc[u][i];
	return anc[u][0];
}

i64 dfs2(int u, int p) {
	for (int to : gr[u]) if (to != p) v[u] += dfs2(to, u);
	return v[u];
}

int main() {
	fastIO();
	cin >> n >> d;
	
	for (int i = 0; i < n-1; ++i) {
		cin >> a >> b, --a, --b;
		gr[a].eb(b);
		gr[b].eb(a);
	}

	cin >> m;
	while (m--) {
		cin >> a, --a;
		cin >> c[a];
	}

	dfs(0, 0);

	cin >> q;
	while (q--) {
		cin >> a >> b >> w, --a, --b;
		int lc = lca(a, b);
		v[a] += w;
		v[b] += w;
		v[lc] -= w;
		v[anc[lc][0]] -= w;
	}

	dfs2(0, 0);

	for (int i = 0; i < n; ++i) {
		if (c[i] == 0) continue;
		for (int j = d; j >= c[i]; --j) {
			dp[j] = max(dp[j], v[i] + dp[j - c[i]]);
		}
	}

	i64 ans = 0LL;
	for (int i = d; i >= 0; --i) {
		ans = max(ans, dp[i]);
	}

	cout << ans << '\n';

	return 0;
}
