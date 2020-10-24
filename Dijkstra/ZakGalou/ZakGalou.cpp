/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Zak Galou
	Link: https://www.urionlinejudge.com.br/judge/pt/problems/view/1409
	Origin: 2007 SBC Programming Marathon
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
const i64 linf = 0x3f3f3f3f3f3f3f3fLL;
const int maxn = 1e3+5;
const int mod = 1e9+7;

int m, n, g, k;
int c, p;
int a, b;
int cost[maxn], dp[maxn];
i64 dist[maxn];
vi gr[maxn];

int main() {
	fastIO();
	
	while (cin >> m >> n >> g >> k and n) {
		for (int i = 0; i <= 1000; ++i) {
			cost[i] = 0;
			dp[i] = inf;
			dist[i] = linf;
			gr[i].clear();
		}

		dp[0] = 0;
		for (int j = 0; j < m; ++j) {
			cin >> c >> p;
			for (int i = 0; i <= 1000; ++i) {
				if (i <= p) {
					dp[i] = min(dp[i], c);
				} else {
					dp[i] = min(dp[i], c + dp[i-p]);
				}
			}
		}

		while (g--) {
			cin >> a >> b, --a, --b;
			gr[a].pb(b);
			gr[b].pb(a);
		}

		while (k--) {
			cin >> a >> c, --a;
			cost[a] += dp[c];
		}

		priority_queue<ii, vii, greater<ii>> q;
		q.emplace(cost[0], 0);

		dist[0] = cost[0];
		while (!q.empty()) {
			auto [d, u] = q.top(); q.pop();
			if (d > dist[u]) continue;
			for (int to : gr[u]) {
				if (dist[u] + cost[to] < dist[to]) {
					dist[to] = dist[u] + cost[to];
					q.emplace(dist[to], to);
				}
			}
		}

		cout << (dist[n-1] == linf ? -1 : dist[n-1]) << '\n';
	}

	return 0;
}
