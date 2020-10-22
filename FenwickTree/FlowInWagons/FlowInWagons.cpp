/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Flow In Wagons
	Link: https://www.urionlinejudge.com.br/judge/pt/problems/view/2857
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
#define len(x) (int)(x).size()
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

int n, ft[maxn];

void add(int idx, int value) {
	for (; idx <= n; idx += (idx & -idx)) {
		ft[idx] += value;
	}
}

int sum(int idx) {
	int rs = 0;
	for (; idx > 0; idx -= (idx & -idx)) {
		rs += ft[idx];
	}
	return rs;
}

int query(int l, int r) {
	return sum(r) - sum(l-1);
}

int m;
int op, a, b, c, d;

int main() {
	fastIO();

	cin >> n >> m;

	while (m--) {
		cin >> op;
		if (op == 1) {
			cin >> a >> b;
			add(a, b);
		} else {
			cin >> a >> b >> c >> d;
			if (d < a or b < c) {
				cout << query(a, b) + query(c, d) << '\n';
			} else {
				cout << query(min(a, c), max(b, d)) << '\n';
			}
		}
	}

	return 0;
}
