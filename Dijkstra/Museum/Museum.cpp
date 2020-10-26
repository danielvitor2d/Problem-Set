/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Museum
	Link: https://neps.academy/problem/613
	Origin: OBI 2006 - First Phase - Level 2
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
const int maxn = 1e3+5;
const int mod = 1e9+7;

int dist[maxn][maxn];
int cost[maxn];
vii gr[maxn];
vii gt[maxn];
int n, m;

void dijkstra(int v) {
	priority_queue<ii, vii, greater<ii>> pq;
	pq.emplace(cost[v], v);
	while (!pq.empty()) {
		ii tp = pq.top(); pq.pop();
		int u = tp.se;
		if (tp.fi > dist[v][u]) continue;
		for (auto [to, w] : gr[u]) {
			if (dist[v][u] + w + cost[to] < dist[v][to]) {
				dist[v][to] = dist[v][u] + w + cost[to];
				pq.emplace(dist[v][to], to);
			}
		}
	}
}

int a, b, w;
int ans;

int main() {
	fastIO();
	
	cin >> n >> m;

	for (int i = 0; i < n; ++i) {
		cin >> cost[i];
		for (int j = 0; j < n; ++j) dist[i][j] = (i != j ? inf : cost[i]);
	}

	for (int i = 0; i < m; ++i) {
		cin >> a >> b >> w, --a, --b;
		gr[a].eb(b, w);
		gt[b].eb(a, w);
	}

	for (int i = 0; i < n; ++i) {
		dijkstra(i);
	}

	ans = inf;
	for (int i = 0; i < n; ++i) {
		for (auto [p, w] : gt[i]) {
			ans = min(ans, dist[i][p] + w);
		}
	}

	cout << ans << '\n';

	return 0;
}
