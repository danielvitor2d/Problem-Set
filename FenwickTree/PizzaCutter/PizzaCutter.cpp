
/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Pizza Cutter
	Link: https://neps.academy/problem/406, https://www.urionlinejudge.com.br/judge/pt/problems/view/2878
	Origin: SBC Programming Marathon 2018
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
const int maxn = 2e5+5;
const int mod = 1e9+7;

int ft[2][maxn];
int x, y;

void add(int i, int idx, int value) {
	for (; idx < maxn; idx += (idx & -idx)) {
		ft[i][idx] += value;
	}
}

int sum(int i, int idx) {
	int rs = 0;
	for (; idx > 0; idx -= (idx & -idx)) {
		rs += ft[i][idx];
	}
	return rs;
}

int query(int i, int l, int r) {
	return sum(i, r) - sum(i, l-1);
}

vi CH, CV;
int n, m;
int pt;

ii H[maxn];
ii V[maxn];
i64 ans;

int main() {
	fastIO();
	
	cin >> x >> y;
	cin >> n >> m;

	CH.pb(y);
	for (int i = 0; i < n; ++i) {
		cin >> H[i].fi >> H[i].se;
		CH.pb(H[i].fi);
		CH.pb(H[i].se);
	}

	CV.pb(x);
	for (int i = 0; i < m; ++i) {
		cin >> V[i].fi >> V[i].se;
		CV.pb(V[i].fi);
		CV.pb(V[i].se);
	}

	sort(all(CH));
	CH.erase(unique(all(CH)), CH.end());

	sort(all(CV));
	CV.erase(unique(all(CV)), CV.end());

	for (int i = 0; i < n; ++i) {
		H[i].fi = 1 + lower_bound(all(CH), H[i].fi) - CH.begin();
		H[i].se = 1 + lower_bound(all(CH), H[i].se) - CH.begin();
	}

	for (int i = 0; i < m; ++i) {
		V[i].fi = 1 + lower_bound(all(CV), V[i].fi) - CV.begin();
		V[i].se = 1 + lower_bound(all(CV), V[i].se) - CV.begin();
	}

	y = 1 + lower_bound(all(CH), y) - CH.begin();
	x = 1 + lower_bound(all(CV), x) - CV.begin();

	ans = 1LL * (n + 1LL) * (m + 1LL);

	sort(H, H+n);
	for (int i = 0; i < n; ++i) {
		add(0, H[i].se, 1);
		ans += query(0, H[i].se + 1, y);
	}

	sort(V, V+m);
	for (int i = 0; i < m; ++i) {
		add(1, V[i].se, 1);
		ans += query(1, V[i].se + 1, x);
	}

	cout << ans << '\n';

	return 0;
}
