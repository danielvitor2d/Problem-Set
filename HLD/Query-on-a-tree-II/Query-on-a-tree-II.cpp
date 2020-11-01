#include <bits/stdc++.h>
using namespace std;
using i64 = long long int;
using vi64 = vector<i64>;

#define fi first
#define se second

const int maxn = 1e4+5;

struct hld {
	vector<pair<int, int>> gr[maxn];
	int pos[maxn], st[maxn], ID[maxn];
	int pai[maxn], v[maxn];
	int h[maxn], timer;
	int hei[maxn], deep[maxn];

 	//O(n)
	void dfs(int u, int p = -1) {
		st[u] = 1;
		for (auto &e : gr[u]) if (e.fi != p) {
			deep[e.fi] = deep[u] + 1;
			hei[e.fi] = hei[u] + e.se;
			dfs(e.fi, u);
			st[u] += st[e.fi];
			if (st[e.fi] > st[gr[u][0].fi] or gr[u][0].fi == p) swap(e, gr[u][0]);
		}
	}

	//O(n)
	void build_hld(int u, int p = -1) {
		pos[u] = ++timer;
		v[pos[u]] = u;
		for (auto [to, w] : gr[u]) if (to != p) {
			pai[to] = u;
			h[to] = (to == gr[u][0].fi ? h[u] : to);
			build_hld(to, u);
		}
	}

	void build(int root = 0) {
		timer = 0;
		h[root] = 0;
		hei[root] = 0;
		deep[root] = 0;
		dfs(root);
		build_hld(root);
	}

	int kth(int a, int k) {
		// cout << a << ' ' << k << '\n';
		// cout << deep[h[a]] << ' ' << deep[a] << '\n';
		if (deep[a] - deep[h[a]] + 1 >= k) return v[pos[a] - k + 1];
		return kth(pai[h[a]], k - (deep[a] - deep[h[a]] + 1));
	}

	int lca(int a, int b) {
		if (pos[a] < pos[b]) swap(a, b);
		return (h[a] == h[b] ? b: lca(pai[h[a]], b));
	}
	int distw(int a, int b) {
		return hei[a] + hei[b] - 2 * hei[lca(a, b)];
	}
	int dist(int a, int b) {
		return deep[a] + deep[b] - 2 * deep[lca(a, b)];
	}
};

int tc;
int n, a, b, c, k, lca;
string op;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> tc;
	while (tc--) {
		hld my_hld;
		cin >> n;

		for (int i = 0; i < n-1; ++i) {
			cin >> a >> b >> c, --a, --b;
			my_hld.gr[a].emplace_back(b, c);
			my_hld.gr[b].emplace_back(a, c);
		}

		my_hld.build();

		while (cin >> op and op.back() != 'E') {
			cin >> a >> b, --a, --b;
			lca = my_hld.lca(a, b);
			if (op[0] == 'D') {
				cout << my_hld.distw(a, b) << '\n';
			} else {
				cin >> k;
				if (my_hld.deep[a]-my_hld.deep[lca]+1 >= k) {
					cout << 1+my_hld.kth(a, k) << '\n';
				} else {
					cout << 1+my_hld.kth(b, my_hld.dist(a, b)-k+2) << '\n';
				}
			}
		}

		cout << '\n';
	}
	return 0;