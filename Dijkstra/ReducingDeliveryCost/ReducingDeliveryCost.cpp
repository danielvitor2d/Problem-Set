/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Reducing Delivery Cost
	Link: https://codeforces.com/contest/1433/problem/G
	Origin: Codeforces Round #677 (Div. 3)
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

int n, m, k;
vii gr[maxn];
int dist[maxn][maxn];

void dijkstra(int o) {
	priority_queue<ii> pq;
	dist[o][o] = 0;
	pq.emplace(0, o);
	while (!pq.empty()) {
		ii tp = pq.top(); pq.pop();
		if (-tp.fi > dist[o][tp.se]) continue;
		for (ii e : gr[tp.se]) if (dist[o][tp.se] + e.se < dist[o][e.fi]) {
			dist[o][e.fi] = dist[o][tp.se] + e.se;
			pq.emplace(-dist[o][e.fi], e.fi);
		} 
	}
}

int a, b, w;
ii edges[maxn];
ii queries[maxn];
i64 ans;

int main() {
	fastIO();
	
	cin >> n >> m >> k;

	for (int i = 0; i < m; ++i) {
		cin >> a >> b >> w, --a, --b;
		edges[i].fi = a;
		edges[i].se = b;
		gr[a].eb(b, w);
		gr[b].eb(a, w);
	}

	for (int i = 0; i < k; ++i) {
		cin >> a >> b, --a, --b;
		queries[i].fi = a;
		queries[i].se = b;
	}

	for (int i = 0; i < n; ++i) 
		for (int j = 0; j < n; ++j)
			dist[i][j] = inf;

	for (int i = 0; i < n; ++i) { //O(n*m*log(n))
		dijkstra(i);
	}

	ans = linf;
	i64 cost = 0LL;

	for (int j = 0; j < k; ++j)
		cost += dist[queries[j].fi][queries[j].se];

	ans = min(ans, cost);
 
	for (int i = 0; i < m; ++i) { //O(m*k)
		int x = edges[i].fi;
		int y = edges[i].se;
		cost = 0LL;
		for (int j = 0; j < k; ++j) {
			int a = queries[j].fi;
			int b = queries[j].se;
			cost += min({dist[a][b], dist[a][x] + dist[y][b], dist[a][y] + dist[x][b]});
		}
		ans = min(ans, cost);
	}

	cout << ans << '\n';

	return 0;
}