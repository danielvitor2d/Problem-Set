/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Count on a tree II
	Link: https://www.spoj.com/problems/COT2/
	Origin: Unknown
*/
#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define eb emplace_back

const int maxn = 4e4+5;
const int L = 21;

int n, m, w[maxn];
int in[maxn], out[maxn], ID[maxn << 1], timer;
int anc[maxn][L];
vi gr[maxn];

//---------- LCA ------------
void dfs(int u, int p) {
	in[u] = ++timer; ID[timer] = u;
	anc[u][0] = p;
	for (int i = 1; i < L; ++i) anc[u][i] = anc[ anc[u][i-1] ][i-1];
	for (int to : gr[u]) if (to != p) dfs(to, u); 
	out[u] = ++timer; ID[timer] = u;
}

bool is_anc(int u, int v) {
	return (in[u] <= in[v] and out[v] <= out[u]);
}

int lca(int u, int v) {
	if (is_anc(u, v)) return u;
	if (is_anc(v, u)) return v;
	for (int i = L-1; i >= 0; --i) if (!is_anc(anc[v][i], u)) v = anc[v][i];
	return anc[v][0];
}
//-------- FIM LCA ----------

//---------- MO's Algorithm -----------
int freq[maxn], used[maxn];

inline void add(int idx, int &ans) {
	if (++used[idx] == 1) {
		if (++freq[w[idx]] == 1) ++ans;
	} else {
		if (--freq[w[idx]] == 0) --ans;
	}
}

inline void remove(int idx, int &ans) {
	if (--used[idx] == 0) {
		if (--freq[w[idx]] == 0) --ans;
	} else {
		if (++freq[w[idx]] == 1) ++ans;
	}
}

const int BLOCK_SIZE = 800;
struct Query {
	int l, r, lca, idx;
	bool operator < (const Query oth) const {
		if (l / BLOCK_SIZE != oth.l / BLOCK_SIZE) return l < oth.l;
		return (l / BLOCK_SIZE & 1) ? (r < oth.r) : (r > oth.r); 
	}
};

vi mo_s_algorithm(vector<Query> queries) {
	vi answer(queries.size());
	sort(all(queries));
	int l = queries[0].l, r = queries[0].l-1, ans = 0;
	for (Query q : queries) {
		while (q.l < l) add(ID[--l], ans);
		while (r < q.r) add(ID[++r], ans);
		while (l < q.l) remove(ID[l++], ans);
		while (q.r < r) remove(ID[r--], ans);
		int u = ID[l], v = ID[r];
		if (u != q.lca and v != q.lca) add(q.lca, ans);
		answer[q.idx] = ans;
		if (u != q.lca and v != q.lca) remove(q.lca, ans);
	}
	return answer;
}
//-------- FIM MO's Algorithm --------

vector<Query> q;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	cin >> n >> m;

	vi C;
	for (int i = 0; i < n; ++i) {
		cin >> w[i];
		C.pb(w[i]);
	}

	sort(all(C));
	C.erase(unique(all(C)), C.end());

	for (int i = 0; i < n; ++i) {
		w[i] = lower_bound(all(C), w[i]) - C.begin();
	}

	int u, v;
	for (int i = 0; i < n-1; ++i) {
		cin >> u >> v, --u, --v;
		gr[u].pb(v);
		gr[v].pb(u);
	}

	dfs(0, 0);

	q.resize(m);

	for (int i = 0; i < m; ++i) {
		cin >> u >> v, --u, --v;
		q[i].lca = lca(u, v);
		if (in[u] > in[v]) swap(u, v);
		if (u == q[i].lca) q[i].l = in[u], q[i].r = in[v];
		else q[i].l = out[u], q[i].r = in[v];
		q[i].idx = i;
	}

	vi ans = mo_s_algorithm(q);

	for (int x : ans) {
		cout << x << '\n';
	}

	return 0;
}