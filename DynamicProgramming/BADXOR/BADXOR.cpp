/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Bad XOR
	Link: https://www.spoj.com/problems/BADXOR/
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
const int maxn = 2e3+5;
const int mod = 1e8+7;

int a[maxn], b[maxn];
int tc, x, n, m;

int seen[maxn][maxn], timer;
int dp[maxn][maxn];

int solve(int idx, int sum_xor) {
	if (idx == n) return !b[sum_xor];
	if (seen[idx][sum_xor] == timer) return dp[idx][sum_xor];
	seen[idx][sum_xor] = timer;
	int ans = solve(idx + 1, sum_xor);
	ans = (ans + solve(idx + 1, sum_xor ^ a[idx])) % mod;
	return dp[idx][sum_xor] = ans;
}

int main() {
    fastIO();
    cin >> tc;
    for (int cs = 1; cs <= tc; ++cs) {
    	cin >> n >> m;
    	for (int i = 0; i <= (1 << 10); ++i) b[i] = 0;
    	for (int i = 0; i < n; ++i) {
    		cin >> a[i];
    	}
    	for (int i = 0; i < m; ++i) {
    		cin >> x;
    		b[x] = 1;
    	}
    	++timer;
    	cout << "Case " << cs << ": " << solve(0, 0) << '\n';
    }
    return 0;
}

