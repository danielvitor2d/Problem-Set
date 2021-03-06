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

typedef vi::iterator iter;

struct WaveletTree {
	vvi C; int s;

	WaveletTree (vi &A, int sigma) : C(sigma*2), s(sigma) {
		build(A.begin(), A.end(), 0, s-1, 1);
	}

	void build(iter b, iter e, int L, int U, int node) {
		if (L == U) return;
		int M = (L+U)/2;

		// C[u][i] contains number of zeros until position i-1: [0,i)
		C[node].reserve(e-b+1); C[node].push_back(0);
		for (iter it = b; it != e; ++it)
			C[node].push_back(C[node].back() + (*it <= M));

		iter p = stable_partition(b, e, [=] (int i) { return i <= M; });
		
		build(b, p, L, M, 2*node);
		build(p, e, M+1, U, 2*node+1);
	}

	// Count occurrences of number c until position i.
	// ie, occurrences of c in positions [0,i]
	int rank(int c, int i) const {
		// Internally we consider an interval open on the right: [0, i)
		i++;
		int L = 0, U = s-1, node = 1, M, r;
		while (L != U) {
			M = (L+U)/2;
			r = C[node][i]; node *= 2;
			if (c <= M)
				i = r, U = M;
			else
				i -= r, L = M+1, ++node;
		}
		return i;
	}

	// Find the k-th smallest element in positions [i,j].
	// The smallest element is k = 1
	int quantile(int k, int i, int j) const {
	// internally we we consider an interval open on the right:  [i, j)
		++j;
		int L = 0, U = s-1, node = 1, M, ri, rj;
		while (L != U) {
			M = (L+U)/2;
			ri = C[node][i]; rj = C[node][j]; node *= 2;
			if (k <= rj-ri)
				i = ri, j = rj, U = M;
			else
				k -= rj-ri, i -= ri, j -= rj,
					L = M+1, ++node;
		}
		return U;
	}

	// Count number of occurrences of numbers in the range [a, b]
	// present in the sequence in positions [i, j], ie, if representing a grid it
	// counts number of points in the specified rectangle.
	mutable int L, U;
	int range(int i, int j, int a, int b) const {
		if (b < a or j < i) return 0;
		L = a; U = b;
		return range(i, j+1, 0, s-1, 1);
	}

	int range(int i, int j, int a, int b, int node) const {
		if (b < L or U < a) return 0;
		if (L <= a and b <= U) return j-i;
		int M = (a+b)/2, ri = C[node][i], rj = C[node][j];
		return range(ri, rj, a, M, node*2) + 
			   range(i-ri, j-rj, M+1, b, node*2+1);
	}
};

int n, q;

int l, r, nxt[maxn];
vi a, b;

int main() {
	fastIO();
	
	cin >> n >> q;
	a = vi(n);
	b = vi(n);

	for (int i = 1; i <= n; ++i) nxt[i] = inf;

	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}

	for (int i = n-1; i >= 0; --i) {
		if (nxt[a[i]] == inf) {
			b[i] = inf;
			nxt[a[i]] = i;
		} else {
			b[i] = nxt[a[i]];
			nxt[a[i]] = i;
		}
	}

	WaveletTree WT(b, n+1);

	while (q--) {
		cin >> l >> r, --l, --r;
		cout << r-l+1 - WT.range(l, r, 1, r) << '\n';
	}

	return 0;
}
