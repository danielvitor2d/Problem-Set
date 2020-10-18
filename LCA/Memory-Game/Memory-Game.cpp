/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Memory Game
	Link: https://neps.academy/problem/393
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
const int maxn = 5e4+5;
const int mod = 1e9+7;

struct LCA {
	int n, l, timer;
	vi in, out, h;
	vvi gr;
	vvi up;

	void preprocess(int _n) {
		n = _n;
		timer = 0;
		h = vi(n);
		in = vi(n);
		out = vi(n);
		gr = vvi(n, vi());
		l = log2(n+1)+1;
		up = vvi(n, vi(l+1));
	}

	void addEdge(int u, int v) {
		gr[u].pb(v);
	}

	void build() {
		dfs(0, 0, 0);
	}

	void dfs(int u, int p, int d) {
		in[u] = ++timer;

		h[u] = d;
		up[u][0] = p;

		for (int i = 1; i <= l; ++i) {
			up[u][i] = up[ up[u][i-1] ][i-1];
		}

		for (int to : gr[u]) {
			if (to == p) continue;
			dfs(to, u, d + 1);
		}

		out[u] = ++timer;
	}

	bool is_anc(int u, int v) {
		return (in[u] <= in[v] and out[v] <= out[u]);
	}

	int lca(int u, int v) {
		if (is_anc(u, v)) return u;
		if (is_anc(v, u)) return v;
		for (int i = l; i >= 0; --i) {
			if (!is_anc(up[v][i], u)) {
				v = up[v][i];
			}
		}
		return up[v][0];
	}
};

int n, x, a, b;
ii m[maxn];
LCA S;
i64 ans;

int main() {
	fastIO();
	cin >> n;
	for (int i = 0; i < n; ++i) m[i].fi = m[i].se = -1;

	for (int i = 0; i < n; ++i) {
		cin >> x, --x;
		if (m[x].fi == -1) m[x].fi = i;
		else m[x].se = i;
	}

	S.preprocess(n);

	for (int i = 0; i < n-1; ++i) {
		cin >> a >> b, --a, --b;
		S.addEdge(a, b);
		S.addEdge(b, a);
	}

	S.build();

	for (int i = 0; i < n/2; ++i) {
		int lca = S.lca(m[i].fi, m[i].se);
		ans += S.h[m[i].fi] + S.h[m[i].se] - 2 * S.h[lca];
	}

	cout << ans << '\n';

	return 0;
}