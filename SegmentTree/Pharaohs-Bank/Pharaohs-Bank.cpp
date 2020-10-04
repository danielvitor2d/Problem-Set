/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Pharaoh's Bank
	Link: https://www.urionlinejudge.com.br/judge/en/problems/view/2071
	Origin: XIV IME-USP Programming Marathon, 2010
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
const i64 linf = 1e15;
const int maxn = 1e5+5;
const int mod = 1e9+7;

struct SegmentTree {

	struct Node {
		pair<i64, int> ans, pref, suff, sum;
		Node(i64 x, int c = 1) {
			ans = pref = suff = sum = {x, c};
		}
		Node () {}
	};

	Node join(const Node& a, const Node& b) {
		Node ans;
		ans.pref = max(a.pref, {a.sum.fi + b.pref.fi, a.sum.se + b.pref.se});
		ans.suff = max({a.suff.fi + b.sum.fi, a.suff.se + b.sum.se}, b.suff);
		ans.sum = {a.sum.fi + b.sum.fi, a.sum.se + b.sum.se};
		ans.ans = max({a.suff.fi + b.pref.fi, a.suff.se + b.pref.se}, max(a.ans, b.ans));
		return ans;
	}

	Node tree[4*maxn];

	void build(int node, int l, int r, vector<int> &v) {
		if (l == r) {
			tree[node] = Node(v[l]);
			return;
		}
		int mid = (l+r)/2;
		int lc = (node << 1);
		build(lc, l, mid, v);
		build(lc+1, mid+1, r, v);
		tree[node] = join(tree[lc], tree[lc+1]);
	}

	void update(int node, int l, int r, int idx, int value) {
		if (l == r) {
			tree[node] = Node(value);
			return;
		}
		int mid = (l+r)/2;
		int lc = (node << 1);
		if(idx <= mid) update(lc, l, mid, idx, value);
		else update(lc+1, mid+1, r, idx, value);
		tree[node] = join(tree[lc], tree[lc+1]);
	}

	Node query(int node, int l, int r, int ql, int qr) {
		if (r < l or qr < l or r < ql) return Node(-linf, 0);
		if (ql <= l and r <= qr) return tree[node];
		int mid = (l+r)/2;
		int lc = (node << 1);
		return join(query(lc, l, mid, ql, min(qr, mid)), 
					query(lc+1, mid+1, r, max(ql, mid+1), qr));
	}

};

int tc, n, q, a, b;
SegmentTree T;
pair<i64, int> rs;
vi v;

int main() {
    fastIO();
    cin >> tc;
    while (tc--) {
    	cin >> n;
    	v = vi(n+1);

    	for (int i = 1; i <= n; ++i) {
    		cin >> v[i];
    	}

    	T.build(1, 1, n, v);

    	cin >> q;
    	while (q--) {
    		cin >> a >> b;
    		rs = T.query(1, 1, n, a, b).ans;
    		cout << rs.fi << ' ' << rs.se << '\n';
    	}
    }
    return 0;
}

