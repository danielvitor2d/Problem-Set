/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Christmas Tree
	Link: https://www.urionlinejudge.com.br/judge/en/problems/view/2026
	Origin: Christmas Contest 2015
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
const int maxn = 1e2+5;
const int mod = 1e9+7;

int tc, n, s;
int p[maxn], c[maxn];
int dp[1010];

int main() {
    fastIO();
    cin >> tc;
    for (int t = 1; t <= tc; ++t) {
    	cin >> n >> s;
    	for (int i = 0; i < n; ++i) {
    		cin >> p[i] >> c[i];
    	}
    	for (int i = 0; i <= s; ++i) dp[i] = 0;
    	for (int i = 0; i < n; ++i) {
    		for (int j = s; j >= c[i]; --j) {
    			dp[j] = max(dp[j], dp[j-c[i]] + p[i]);
    		}
    	}
    	cout << "Galho " << t << ":\n";
    	cout << "Numero total de enfeites: " << dp[s] << "\n\n";
    }
    return 0;
}

