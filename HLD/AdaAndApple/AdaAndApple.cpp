#include <bits/stdc++.h>
using namespace std;
using i64 = long long int;
using vi64 = vector<i64>;

const int maxn = 3e5+5;

namespace SegmentTree {

	struct Node {
		i64 val;
		Node(i64 x) : val(x) {}
		Node () : val(0LL) {}
	};

	inline Node join(const Node &a, const Node &b) {
		return Node(a.val + b.val);
	}

	int n;
	Node tree[4*maxn];
	Node neutral;

	void build(int node, int l, int r, int *v) {
		if (l == r) { tree[node].val = v[l]; return; }
		int mid = l+(r-l)/2, lc = (node << 1);
		build(lc, l, mid, v);
		build(lc+1, mid+1, r, v);
		tree[node] = join(tree[lc], tree[lc+1]);
	}

	void update(int node, int l, int r, int idx, i64 val) {
		if (l == r) {
			tree[node].val = val;  //to set value
			//tree[node].val += val;  //to increment value
			return;
		}
		int mid = l+(r-l)/2, lc = (node << 1);
		if(idx <= mid) update(lc, l, mid, idx, val);
		else update(lc+1, mid+1, r, idx, val);
		tree[node] = join(tree[lc], tree[lc+1]);
	}

	Node query(int node, int l, int r, int ql, int qr) {
		if (r < l or qr < l or r < ql) return neutral;
		if (ql <= l and r <= qr) return tree[node];
		int mid = l+(r-l)/2, lc = (node << 1);
		return join(query(lc, l, mid, ql, min(qr, mid)), query(lc+1, mid+1, r, max(ql, mid+1), qr));
	}

	void build(int _n, int *v) {
		n = _n;
		build(1, 1, n, v);
	}

	i64 query(int l, int r) {
		return query(1, 1, n, l, r).val;
	}

	void update(int idx, int val) {
		update(1, 1, n, idx, val);
	}
};

namespace HLD {
	struct edge {
		int a; i64 w;
		edge () {}
		edge (int to, i64 ww) : a(to), w(ww) {}
	};

	vector<edge> gr[maxn];
	int pos[maxn], st[maxn], pai[maxn];
	int h[maxn], v[maxn], val[maxn], timer;
	int deep[maxn], hei[maxn];

	inline void addEdge(int a, int b, i64 w = 1) {
		gr[a].push_back(edge(b, w));
	}

 	//O(n)
	void dfs(int u, int p = -1) {
		st[u] = 1;
		for (auto &e : gr[u]) if (e.a != p) {
			pai[e.a] = u;
			deep[e.a] = deep[u] + 1;
			hei[e.a] = hei[u] + e.w;
			dfs(e.a, u);
			st[u] += st[e.a];
			if (st[e.a] > st[gr[u][0].a] or gr[u][0].a == p) swap(e, gr[u][0]);
		}
	}

	//O(n)
	void build_hld(int u, int p = -1) {
		pos[u] = ++timer;
		v[pos[u]] = val[u];
		for (auto e : gr[u]) if (e.a != p) {
			h[e.a] = (e.a == gr[u][0].a ? h[u] : e.a);
			build_hld(e.a, u);
		}
	}

	void build(int root = 0) {
		timer = 0;
		h[root] = 0;
		hei[root] = 0;
		deep[root] = 0;
		dfs(root);
		build_hld(root);
		SegmentTree::build(timer, v);
	}

	//O(log^2 (n))
	i64 query_path(int a, int b) {
		if (pos[a] < pos[b]) swap(a, b);
		if (h[a] == h[b]) return SegmentTree::query(pos[b], pos[a]);
		return SegmentTree::query(pos[h[a]], pos[a]) + query_path(pai[h[a]], b);
	}
	
	//O(log^2 (n))
	void update_point(int a, i64 x) {
		SegmentTree::update(pos[a], x);
	}

	int lca(int a, int b) {
		if (pos[a] < pos[b]) swap(a, b);
		return (h[a] == h[b] ? b : lca(pai[h[a]], b));
	}

	int dist(int a, int b) {
		return (deep[a] + deep[b] - 2 * deep[lca(a, b)]);
	}
};

int n, q, a, b;
int op, v[maxn];

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> n >> q;

	char c;
	for (int i = 0; i < n; ++i) {
		cin >> c;
		HLD::val[i] = c-'0';
		v[i] = HLD::val[i];
	}

	for (int i = 0; i < n-1; ++i) {
		cin >> a >> b;
		HLD::addEdge(a, b);
		HLD::addEdge(b, a);
	}

	HLD::build();

	while (q--) {
		cin >> op;
		if (op == 0) {
			cin >> a;
			v[a] ^= 1;
			HLD::update_point(a, v[a]);
		} else {
			cin >> a >> b;
			i64 s1 = HLD::query_path(a, b);
			if (s1 == 0 or s1 == HLD::dist(a, b)+1) {
				cout << "YES\n";
			} else {
				cout << "NO\n";
			}
		}
	}

	return 0;
}
