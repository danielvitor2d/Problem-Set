/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Ant Colony
	Link: https://neps.academy/problem/333
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
const int mod = 1e9+7;

struct LCA {
	int n, l, timer;
	i64 w[maxn];
	vector<int> in, out;
	vector<vector<ii>> gr;
	vector<vector<int>> up;

	void preprocess(int _n) {
		n = _n;
		timer = 0;
		in = vector<int>(n);
		out = vector<int>(n);
		gr = vector<vector<ii>>(n, vector<ii>());
		l = log2(n+1)+1;
		up = vector<vector<int>>(n, vector<int>(l+1));
	}

	void addEdge(int u, int v, int ww) {
		gr[u].eb(v, ww);
	}

	void build() {
		dfs(0, 0, 0);
	}

	void dfs(int u, int p, i64 we) {
		in[u] = ++timer;
		w[u] = we;

		up[u][0] = p;

		for (int i = 1; i <= l; ++i) {
			up[u][i] = up[ up[u][i-1] ][i-1];
		}

		for (auto [to, ww] : gr[u]) {
			if (to == p) continue;
			dfs(to, u, we + ww);
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

LCA S;
int n, q, a, b;

int main() {
	fastIO();

	while (cin >> n and n) {
		S.preprocess(n);

		for (int i = 1; i <= n-1; ++i) {
			cin >> a >> b;
			S.addEdge(a, i, b);
			S.addEdge(i, a, b);
		}

		S.build();

		cin >> q;
		while (q--) {
			cin >> a >> b;
			cout << S.w[a] + S.w[b] - 2 * S.w[S.lca(a, b)] << ' ';
		}
		cout << '\n';
	}

	return 0;
}
