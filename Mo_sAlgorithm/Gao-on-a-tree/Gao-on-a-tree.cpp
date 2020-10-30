/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Gao on a tree
	Link: https://br.spoj.com/problems/GOT/
	Origin: SPOJ Brasil
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<i64> vi64;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define fastio ios_base::sync_with_stdio(0), cin.tie(0)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define ms(a, x) memset(a, x, sizeof(a))
#define len(x) (int)(x).size()
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

const int inf = 0x3f3f3f3f;
const int maxn = 2e5+5;
const int mod = 1e9+7;

const int BLOCK_SIZE = 800;
const int L = 25;

int n, m, a, b, c, l;
int anc[maxn][L], tin[maxn], tout[maxn], ID[maxn << 1], timer;
vi gr[maxn];

int v[maxn], f[maxn], used[maxn];

inline void init() {
	for (int i = 0; i <= n; ++i) {
		f[i] = 0;
		used[i] = 0;
	}
}

inline void remove(int idx) {
	if (--used[idx] == 0) --f[v[idx]];
	else ++f[v[idx]];
}

inline void add(int idx) {
	if (++used[idx] == 1) ++f[v[idx]];
	else --f[v[idx]];
}

inline int get_answer(int value) {
	return (f[value] > 0);
}

struct Query {
	int l, r, c, lca, idx;
	bool operator < (const Query oth) const {
		if (l / BLOCK_SIZE != oth.l / BLOCK_SIZE) return l < oth.l;
		return (l / BLOCK_SIZE & 1) ? (r < oth.r) : (r > oth.r); 
	}
};

vi mo_s_algorithm(vector<Query> queries) {
	vi answers(queries.size());
	sort(queries.begin(), queries.end());
	init();
	int l = queries[0].l, r = queries[0].l-1;
	for (Query q : queries) {
		while (q.l < l) add(ID[--l]);
		while (r < q.r) add(ID[++r]);
		while (l < q.l) remove(ID[l++]);
		while (q.r < r) remove(ID[r--]);
		if (ID[l] != q.lca and ID[r] != q.lca) add(q.lca);
		answers[q.idx] = get_answer(q.c);
		if (ID[l] != q.lca and ID[r] != q.lca) remove(q.lca);
	}
	return answers;
}

bool is_anc(int u, int v) {
	return tin[u] <= tin[v] and tout[v] <= tout[u];
}

int lca(int u, int v) {
	if (is_anc(u, v)) return u;
	if (is_anc(v, u)) return v;
	for (int i = L-1; i >= 0; --i) {
		if (!is_anc(anc[u][i], v)) {
			u = anc[u][i];
		}
	}
	return anc[u][0];
}

void dfs(int u, int p) {
	tin[u] = ++timer; ID[timer] = u;

	anc[u][0] = p;
	for (int i = 1; i < L; ++i) {
		anc[u][i] = anc[ anc[u][i-1] ][i-1];
	}

	for (int to : gr[u]) if (to != p) {
		dfs(to, u);
	}

	tout[u] = ++timer; ID[timer] = u;
}

int main() {
	fastio;
	
	while (cin >> n >> m and n) {
		for (int i = 0; i < n; ++i) {
			cin >> v[i];
		}
		for (int i = 0; i < n-1; ++i) {
			cin >> a >> b, --a, --b;
			gr[a].eb(b);
			gr[b].eb(a);
		}
		dfs(0, 0);
		vector<Query> q(m);
		for (int i = 0; i < m; ++i) {
			cin >> a >> b >> c, --a, --b;
			l = lca(a, b);
			if (tin[a] > tin[b]) swap(a, b);
			if (a == l) q[i].l = tin[a], q[i].r = tin[b];
			else q[i].l = tout[a], q[i].r = tin[b];
			q[i].c = c;
			q[i].lca = l;
			q[i].idx = i;
		}
		vi ans = mo_s_algorithm(q);
		for (int x : ans) {
			cout << (x ? "Find\n" : "NotFind\n");
		}
		cout << '\n';
		timer = 0;
		for (int i = 0; i < n; ++i) {
			gr[i].clear();
			for (int j = 0; j < L; ++j) anc[i][j] = 0;
		}
	}

	return 0;
}

/*
5 5
1 2 3 4 5
1 2
1 3
3 4
3 5
2 3 4
2 4 3
2 4 5
4 5 1
4 5 3

NotFind
Find
NotFind
NotFind
Find
*/