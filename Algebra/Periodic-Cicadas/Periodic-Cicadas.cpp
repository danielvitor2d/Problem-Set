/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Periodic Cicadas
	Link: https://www.urionlinejudge.com.br/judge/en/problems/view/2660
	Origin: SBC Programming Marathon - ACM ICPC - 2017
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
const int maxn = 2e5+5;
const int mod = 1e9+7;

i64 gcd(i64 a, i64 b) { return (b == 0 ? a : gcd(b, a%b)); }
i64 lcm(i64 a, i64 b) { return (a/gcd(a, b)*b); }

i64 n, l, a, x, d, ans, mx;


int main() {
    fastIO();
    cin >> n >> l;

    a = 1;
    for (int i = 0; i < n; ++i) {
    	cin >> x;
    	a = lcm(a, x);
    }

    for (int i = 1; i <= l; ++i) {
    	d = lcm(a, i);
    	if (d <= l and d > mx) {
    		mx = d;
    		ans = i;
    	}
    }

    cout << ans << '\n';

    return 0;
}

