/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Letters
	Link: https://neps.academy/problem/61
	Origin: OBI 2015 - Second Phase - Level 1
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
const int maxn = 3e5+5;
const int mod = 1e9+7;

int dp[maxn][26];
string s;

int solve(int idx, int last) {
	if (idx == (int)s.size()) return 0;
	if (~dp[idx][last]) return dp[idx][last];
	int ans = 0;
	ans = max(ans, solve(idx+1, last));
	if (s[idx]-'A' >= last) ans = max(ans, 1+solve(idx+1, s[idx]-'A'));
	return dp[idx][last] = ans;
}

int main() {
    fastIO();
    cin >> s;
    for (int i = 0; i < (int)s.size(); ++i) 
    	for (int j = 0; j < 26; ++j) dp[i][j] = -1; 
    cout << solve(0, 0) << '\n';
    return 0;
}

