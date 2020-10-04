/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Coin Boxes
	Link: https://neps.academy/problem/347
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

struct SegmentTree {

	struct Node {
		i64 value;
		Node(i64 x) : value(x) {}
		Node () : value(0LL) {}
	};

	Node join(const Node& a, const Node& b) {
		return Node(a.value + b.value);
	}

	i64 lazy[4*maxn];
	Node tree[4*maxn];

	void upLazy(int node, int l, int r) {
		if (lazy[node] == -1LL) return;
		tree[node].value = lazy[node] * 1LL * (r - l + 1LL);
		if (l != r) {
			int lc = (node << 1);
			lazy[lc] = lazy[node];
			lazy[lc+1] = lazy[node];
		}
		lazy[node] = -1LL;
	}

	void build(int node, int l, int r, vi64 &v) {
		lazy[node] = -1LL;
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

	void update(int node, int l, int r, int ul, int ur, i64 value) {
		upLazy(node, l, r);
		if (r < l or ur < ul or ur < l or r < ul) return;
		if (ul <= l and r <= ur) {
			lazy[node] = value;
			upLazy(node, l, r);
			return;
		}
		int mid = (l+r)/2;
		int lc = (node << 1);
		update(lc, l, mid, ul, ur, value);
		update(lc+1, mid+1, r, ul, ur, value);
		tree[node] = join(tree[lc], tree[lc+1]);
	}

	Node query(int node, int l, int r, int ql, int qr) {
		upLazy(node, l, r);
		if (r < l or qr < ql or qr < l or r < ql) return Node(0LL);
		if (ql <= l and r <= qr) return tree[node];
		int mid = (l+r)/2;
		int lc = (node << 1);
		return join(query(lc, l, mid, ql, qr),
					query(lc+1, mid+1, r, ql, qr));
	}

};

SegmentTree T;
int n, q, op, a, b;
i64 k;
vi64 v;

int main() {
    fastIO();

    cin >> n >> q;

    for (int i = 0; i < 4 * maxn; ++i) {
    	T.lazy[i] = -1;
    }

    v = vi64(n+1);
    for (int i = 1; i <= n; ++i) {
    	cin >> v[i];
    }

    T.build(1, 1, n, v);

    while (q--) {
    	cin >> op >> a >> b;
    	if (op == 1) {
    		cin >> k;
    		T.update(1, 1, n, a, b, k);
    	} else {
    		cout << T.query(1, 1, n, a, b).value << '\n';
    	}
    }

    return 0;
}

