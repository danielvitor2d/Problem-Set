/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Smider Pan
	Link: https://www.urionlinejudge.com.br/judge/en/problems/view/2943
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
const int maxn = 1e3+5;
const int mod = 1e9+7;

int n, h[maxn], res;
int dp[maxn][2];

int main() {
	fastIO();

	cin >> n;

	for (int i = 1; i <= n; ++i) {
		cin >> h[i];
	}

	dp[0][0] = 1;

	for (int i = 1; i <= n; ++i) {
		for (int j = i-1; j >= 0; --j) {
			if (h[i] < h[j]) {
				dp[i][1] = max(dp[i][1], 1 + max(dp[j][0], dp[j][1]));
			}
			if (h[i] > h[j]) {
				dp[i][0] = max(dp[i][0], 1 + dp[j][0]);
			}
			res = max(res, dp[i][0]);
			res = max(res, dp[i][1]);
		}
	}

	cout << res << '\n';

	return 0;
}