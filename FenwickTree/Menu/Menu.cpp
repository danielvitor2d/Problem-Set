/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Menu
	Link: https://www.urionlinejudge.com.br/judge/en/problems/view/2526
	Origin: 6th Selective Process UFPR
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
const int maxn = 1e6+5;
const int mod = 1e9+7;

struct FenwickTree {

	int tree[maxn], a[maxn];
	int n;

	void build(int _n) {
		n = _n;
		for (int i = 0; i < maxn; ++i) {
			tree[i] = 0;
		}
	}

	void updateI(int idx, int x) {   //increment a[idx] by x
		a[idx] = x;
		for (; idx <= n; idx += (idx & -idx)) {
			tree[idx] += x;
		}
	}

	void updateS(int idx, int x) {   //set a[idx] = x
		int delta = x - a[idx];
		a[idx] = x;
		for (; idx <= n; idx += (idx & -idx)) {
			tree[idx] += delta;
		}
	}

	int query(int idx) {            //return sum of a[1..idx]
		int rs = 0;
		for (; idx > 0; idx -= (idx & -idx)) {
			rs += tree[idx];
		}
		return rs;
	}

	int query(int l, int r) {       //return sum of a[l..r]
		return query(r) - query(l - 1);
	}

};

FenwickTree L, R;
int n, v[maxn];
i64 ans;

int main() {
	fastIO();
	
	while (cin >> n and n) {
		L.build(n);
		R.build(n);
		ans = 0LL;

		for (int i = 1; i <= n; ++i) {
			cin >> v[i];
			R.updateI(v[i], 1);
		}

		for (int i = 1; i <= n; ++i) {
			L.updateI(v[i], 1);
			ans += L.query(v[i] + 1, n) * 1LL * R.query(1, v[i] - 1);
			R.updateI(v[i], -1);
		}

		cout << ans << '\n';
	}

	return 0;
}