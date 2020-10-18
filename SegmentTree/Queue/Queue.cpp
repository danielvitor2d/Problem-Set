/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Queue
	Link: https://neps.academy/problem/67
	Origin: OBI 2015 - Second phase - Level 2
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
const int maxn = 2e6+5;
const int mod = 1e9+7;

int t[maxn], p[maxn], x[maxn], h[maxn];

int ft[maxn], st[4*maxn];
int n, q;

//--------- Segment Tree ------------
void update(int node, int l, int r, int pos, int value) {
	if (l == r) {
		st[node] = value;
		return;
	}
	int mid = l + (r - l)/2;
	int lc = (node << 1);
	if (pos <= mid) update(lc, l, mid, pos, value);
	else update(lc+1, mid+1, r, pos, value);
	st[node] = max(st[lc], st[lc+1]);
}

int get_max(int node, int l, int r, int idx, int x) {
	if (st[node] <= x or idx < l) return 0;
	if (l == r) return l;
	int mid = l + (r - l)/2;
	int lc = (node << 1);
	if (idx < r) return max(get_max(lc, l, mid, idx, x), get_max(lc+1, mid+1, r, idx, x));
	if (st[lc+1] > x) return get_max(lc+1, mid+1, r, idx, x);
	return get_max(lc, l, mid, idx, x);	
}
//--------- End Segment Tree -----------
//---------- Fenwick Tree ------------
int search(int x) {
	int pos = 0;
	for (int i = 25; i >= 0; --i) {
		if (pos + (1 << i) <= n+q and ft[pos + (1 << i)] <= x) {
			x -= ft[pos + (1 << i)];
			pos += (1 << i);
		}
	}
	return pos;
}

void add(int idx, int value) {
	for (; idx <= n+q; idx += (idx & -idx)) {
		ft[idx] += value;
	}
}

int sum(int idx) {
	int res = 0;
	for (; idx > 0; idx -= (idx & -idx)) {
		res += ft[idx];
	}
	return res;
}
//-------- End Fenwick Tree -----------

int main() {
	fastIO();

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> x[i];
		p[i] = i;
	}

	cin >> q;

	for (int i = n; i < n+q; ++i) {
		cin >> t[i] >> p[i] >> x[i];
	}

	for (int i = 1; i <= n+q; ++i) {
		add(i, 1);
	}

	for (int i = n+q-1; i >= 0; --i) {
		if (t[i] == 0) {
			p[i] = 1 + search(p[i]);
			add(p[i], -1);
		} else {
			p[i] = 1 + search(p[i]-1);
		}
	}

	for (int i = 0; i < n+q; ++i) {
		if (t[i] == 0) {
			h[p[i]] = x[i];
			update(1, 1, n+q, p[i], h[p[i]]);
			add(p[i], 1);
		} else {
			cout << sum(get_max(1, 1, n+q, p[i], h[p[i]] + x[i])) << '\n';
		}
	}

	return 0;
}
