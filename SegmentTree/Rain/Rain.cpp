/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Rain
	Link: https://neps.academy/problem/58
	Origin: OBI 2016 - First Phase - Level 2
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
		int value;
		Node(int x) : value(x) {}
		Node () : value(0) {}
	};

	Node join(const Node& a, const Node& b) {
		return Node(max(a.value, b.value));
	}

	Node tree[4*maxn];
	Node neutral;

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
			tree[node] = value;
			return;
		}
		int mid = (l+r)/2;
		int lc = (node << 1);
		if(idx <= mid) update(lc, l, mid, idx, value);
		else update(lc+1, mid+1, r, idx, value);
		tree[node] = join(tree[lc], tree[lc+1]);
	}

	Node query(int node, int l, int r, int ql, int qr) {
		if (r < l or qr < l or r < ql) return neutral;
		if (ql <= l and r <= qr) return tree[node];
		int mid = (l+r)/2;
		int lc = (node << 1);
		return join(query(lc, l, mid, ql, min(qr, mid)), 
					query(lc+1, mid+1, r, max(ql, mid+1), qr));
	}

};

int n, ans;
SegmentTree T;
vi h;

int main() {
    fastIO();

    cin >> n;
    h = vi(n+1);

    for (int i = 1; i <= n; ++i) {
    	cin >> h[i];
    }

    T.build(1, 1, n, h);

    for (int i = 2; i <= n-1; ++i) {
    	if (T.query(1, 1, n, 1, i-1).value > h[i] and 
    		T.query(1, 1, n, i+1, n).value > h[i]) {
    		++ans;
    	}
    }

    cout << ans << '\n';

    return 0;
}

