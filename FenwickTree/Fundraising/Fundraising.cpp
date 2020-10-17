/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Fundraising
	Link: https://www.urionlinejudge.com.br/judge/en/problems/view/2700
	Origin: ACM/ICPC Latin American Regional 2017
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

i64 ft[maxn];
int top;

void upd(int idx, i64 value) {
	for (;idx <= top; idx += (idx & -idx)) {
		ft[idx] = max(ft[idx], value);
	}
}

i64 get_max(int idx) {
	i64 ans = 0;
	for (; idx > 0; idx -= (idx & -idx)) {
		ans = max(ans, ft[idx]);
	}
	return ans;
}

struct p {
	int b, f;
	i64 d;
	bool operator < (const p &oth) const {
		if (b == oth.b) return f > oth.f;
		return b < oth.b;
	}
};

bool cmp(p &a, p &b) {
	if (a.b == b.b) return a.f < b.f;
	return a.b < b.b;
}

p arr[maxn];
vector<p> v;

int n, sz;
i64 ans;

int main() {
	fastIO();
	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> arr[i].b >> arr[i].f >> arr[i].d;
	}

	sort(arr, arr+n, cmp);

	v.pb(arr[0]);
	for (int i = 1; i < n; ++i) {
		if (arr[i].b == v.back().b and arr[i].f == v.back().f) {
			v.back().d += arr[i].d;
		} else {
			v.pb(arr[i]);
		}
	}

	sz = v.size();
	vi C;
	for (int i = 0; i < sz; ++i) {
		C.pb(v[i].f);
	}

	sort(all(C));
	C.erase(unique(all(C)), C.end());

	top = C.size();

	for (int i = 0; i < sz; ++i) {
		v[i].f = 1 + (lower_bound(all(C), v[i].f) - C.begin());
	}

	sort(all(v));

	for (int i = 0; i < sz; ++i) {
		upd(v[i].f, v[i].d + get_max(v[i].f - 1));
	}

	cout << get_max(top) << '\n';

	return 0;
}