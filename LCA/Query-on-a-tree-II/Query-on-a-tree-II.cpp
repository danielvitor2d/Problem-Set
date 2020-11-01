#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;

const int maxn = 1e4+5;
const int L = 21;

namespace LCA {
	int anc[maxn][L], tin[maxn], tout[maxn], deep[maxn], h[maxn];
	vector<ii> gr[maxn];
	int n, timer;

	inline void init(int _n) {
		n = _n;
		timer = 0;
		for (int i = 0; i < n; ++i) {
			deep[i] = 0;
			h[i] = 0;
			tin[i] = tout[i] = 0;
			gr[i].clear();
			for (int j = 0; j < L; ++j) anc[i][j] = 0;
		}
	}

	void dfs(int u, int p) {
		tin[u] = ++timer;
		anc[u][0] = p;
		for (int i = 1; i < L; ++i) anc[u][i] = anc[ anc[u][i-1] ][i-1];
		for (auto [to, w] : gr[u]) if (to != p) {
			deep[to] = deep[u] + 1;
			h[to] = h[u] + w;
			dfs(to, u);
		}
		tout[u] = ++timer;
	}

	inline void addEdge(int u, int v, int w) {
		gr[u].emplace_back(v, w);
	}

	inline bool is_anc(int u, int v) {
		return (tin[u] <= tin[v] and tout[v] <= tout[u]);
	}

	inline int lca(int u, int v) {
		if (is_anc(u, v)) return u;
		if (is_anc(v, u)) return v;
		for (int i = L-1; i >= 0; --i) if (!is_anc(anc[u][i], v)) u = anc[u][i];
		return anc[u][0]; 
	}

	inline int kth_anc(int u, int k) {
		if (--k == 0) return u;
		for (int i = L-1; i >= 0; --i) {
			if (k - (1 << i) >= 0) {
				u = anc[u][i];
				k -= (1 << i);
			}
		}
		return u;
	}

	inline int dist_w(int a, int b) {
		return h[a] + h[b] - 2 * h[lca(a, b)];
	}

	inline int dist(int a, int b) {
		return deep[a] + deep[b] - 2 * deep[lca(a, b)];
	}

	inline void build() {
		dfs(0, 0);
	}
};

int tc;
int n, a, b, c, k, lca;
string op;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> tc;
	while (tc--) {
		cin >> n;
		LCA::init(n);
		for (int i = 0; i < n-1; ++i) {
			cin >> a >> b >> c, --a, --b;
			LCA::addEdge(a, b, c);
			LCA::addEdge(b, a, c);
		}
		LCA::build();
		while (cin >> op and op.back() != 'E') {
			cin >> a >> b, --a, --b;
			if (op[0] == 'D') {
				cout << LCA::dist_w(a, b) << '\n';
			} else {
				cin >> k;
				lca = LCA::lca(a, b);
				if (LCA::dist(a, lca)+1 >= k) {
					cout << 1+LCA::kth_anc(a, k) << '\n';
				} else {
					cout << 1+LCA::kth_anc(b, LCA::dist(a, b)-k+2) << '\n';
				}
			}
		}
		cout << '\n';
	}
	return 0;
}