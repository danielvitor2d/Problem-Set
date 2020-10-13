/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: First Promotion
	Link: https://neps.academy/problem/823
	Origin: OBI 2020 - First Phase - Level 2
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
const int maxn = 5e4+5;
const int mod = 1e9+7;

int n, a, b, e, ans;
vii gr[maxn];
int dp[maxn][2];

int solve(int u, int cl) {
	if (~dp[u][cl]) return dp[u][cl];

	int rs = 1;

	for (auto [to, e] : gr[u]) {
		if (e != cl) {
			rs = max(rs, 1 + solve(to, e));
		}
	}

	return dp[u][cl] = rs;
}

int main() {
	fastIO();

	cin >> n;

	for (int i = 1; i <= n; ++i) dp[i][0] = dp[i][1] = -1;

	for (int i = 0; i < n-1; ++i) {

		cin >> a >> b >> e;

		gr[a].eb(b, e);
		gr[b].eb(a, e);

	}	

	for (int i = 1; i <= n; ++i) {
		ans = max(ans, solve(i, 0));
		ans = max(ans, solve(i, 1));
	}

	cout << ans << '\n';

	return 0;
}