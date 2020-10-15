/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Range Set Query
	Link: https://atcoder.jp/contests/abc174/tasks/abc174_f
	Origin: AtCoder Beginner Contest 174
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
const int maxn = 5e5+5;
const int mod = 1e9+7;

struct SegmentTree {

	struct Node {
		vi v;
	};

	Node join(const Node &a, const Node &b) {
		Node ans;
		merge(all(a.v), all(b.v), back_inserter(ans.v));
		return ans;
	}

	Node tree[4*maxn];
	Node neutral;

	void build(int node, int l, int r, vi &v) {
		if (l == r) {
			tree[node].v.pb(v[l]);
			return;
		}
		int mid = (l+r)/2;
		int lc = (node << 1);
		build(lc, l, mid, v);
		build(lc+1, mid+1, r, v);
		tree[node] = join(tree[lc], tree[lc+1]);
	}

	int query(int node, int l, int r, int ql, int qr, int x) { 
		if (r < l or qr < l or r < ql) return 0;
		if (ql <= l and r <= qr) return upper_bound(all(tree[node].v), x) - tree[node].v.begin(); //Count the numbers less or equal x in range [ql, qr]
		int mid = (l+r)/2;
		int lc = (node << 1);
		return query(lc, l, mid, ql, min(qr, mid), x) + 
			   query(lc+1, mid+1, r, max(ql, mid+1), qr, x);
	}
};

SegmentTree T;
int n, l, r, x, q;
int nxt[maxn];
vi a, b;

int main() {
	fastIO();

	cin >> n >> q;

	a = vi(n+1);
	b = vi(n+1);

	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		nxt[i] = -1;
	}

	for (int i = n; i >= 1; --i) {
		if (nxt[a[i]] == -1) {
			b[i] = inf;
			nxt[a[i]] = i;
		} else {
			b[i] = nxt[a[i]];
			nxt[a[i]] = i;
		}
	}

	T.build(1, 1, n, b);

	while (q--) {
		cin >> l >> r;
		cout << (r - l + 1) - T.query(1, 1, n, l, r, r) << '\n';
	}

	return 0;
}