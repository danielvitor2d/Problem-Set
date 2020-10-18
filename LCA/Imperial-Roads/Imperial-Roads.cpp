/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Imperial Roads
	Link: https://www.urionlinejudge.com.br/judge/en/problems/view/2703
	Origin: ACM/ICPC Latin American Regional 2017
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
const int L = 20;

struct edge {
	int a, b, w;
	bool operator < (const edge &oth) const {
		return w < oth.w;
	}
};

int n, m, q;
int a, b, c, w, cost;
vii gr[maxn];
map<ii, int> g;

int in[maxn], out[maxn], timer;
int anc[maxn][L];
int mx[maxn][L];

//----------- LCA -----------
void dfs(int u, int p, int w) {
	in[u] = ++timer;
	anc[u][0] = p;
	mx[u][0] = w;
	for (int i = 1; i < L; ++i) {
		anc[u][i] = anc[ anc[u][i-1] ][i-1];
		mx[u][i] = max(mx[u][i-1], mx[ anc[u][i-1] ][i-1]);
	}
	for (auto [to, ww] : gr[u]) if (p != to) dfs(to, u, ww);
	out[u] = ++timer;
}
bool is_anc(int u, int v) {
	return in[u] <= in[v] and out[v] <= out[u];
}
int lca(int u, int v) {
	if (is_anc(u, v)) return u;
	if (is_anc(v, u)) return v;
	for (int i = L-1; i >= 0; --i) {
		if (!is_anc(anc[u][i], v)) u = anc[u][i];
	}
	return anc[u][0];
}
int up(int u, int v) {
	int ans = -inf;
	for (int i = L-1; i >= 0; --i) {
		if (!is_anc(anc[u][i], v)) {
			ans = max(ans, mx[u][i]);
			u = anc[u][i];
		}
	}
	return max(ans, mx[u][0]);
}
int get_max(int u, int v) {
	if (u == v) return 0;
	if (is_anc(u, v)) return up(v, u);
	if (is_anc(v, u)) return up(u, v);
	return max(up(u, lca(u, v)), up(v, lca(u, v)));
}
//--------- END LCA ---------
//---------- DSU ------------
int link[maxn], sz[maxn];
void init() {
	for (int i = 0; i <= n; ++i) {
		link[i] = i;
		sz[i] = 1;
	}
}
int id(int x) { return link[x] = (link[x] == x ? x : id(link[x])); }
bool same(int u, int v) { return (id(u) == id(v)); }
void unite(int u, int v) {
	u = id(u), v = id(v);
	if (u == v) return;
	if (sz[u] < sz[v]) swap(u, v);
	sz[u] += sz[v];
	link[v] = u;
}
//-------- END DSU ---------
//---------- MST -----------
vector<edge> edges;
void mst() {
	sort(all(edges));
	init();
	for (auto e : edges) {
		if (!same(e.a, e.b)) {
			unite(e.a, e.b);
			cost += e.w;
			gr[e.a].eb(e.b, e.w);
			gr[e.b].eb(e.a, e.w);
		}
	}
}
//--------- END MST ---------

int main() {
	fastIO();
	
	cin >> n >> m;
	edges.resize(m);

	for (int i = 0; i < m; ++i) {
		cin >> edges[i].a >> edges[i].b >> edges[i].w;
		--edges[i].a, --edges[i].b;
		g[{edges[i].a, edges[i].b}] = edges[i].w;
		g[{edges[i].b, edges[i].a}] = edges[i].w;
	}

	mst();

	dfs(0, 0, -inf);

	cin >> q;

	while (q--) {
		cin >> a >> b, --a, --b;
		cout << cost - get_max(a, b) + g[{a, b}] << '\n';
	}

	return 0;
}
