/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Dona Worm
	Link: https://www.urionlinejudge.com.br/judge/pt/problems/view/1711
	Origin: SBC 2014 Programming Marathon
*/
#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

#define fi first
#define se second

const int inf = 0x3f3f3f3f;
const int maxn = 1e4+5;

int n, m, q;
vii gr[maxn];

int color[maxn], cost[maxn], sum;
vii order, cycle;

void dfs(int u, int p, int w) {
	color[u] = 1;
	order.emplace_back(u, w);

	for (auto [to, ww] : gr[u]) {
		if (color[to] == 2 or to == p) continue;
		if (!color[to]) {
			dfs(to, u, ww);
		} else {
			sum = ww;
			while (order.back().fi != to) {
				sum += order.back().se;
				cycle.push_back(order.back());
				order.pop_back();
			}
			cycle.push_back(order.back());
			order.pop_back();
			reverse(cycle.begin(), cycle.end());
			while (!cycle.empty()) {
				cost[cycle.back().fi] = sum;
				order.push_back(cycle.back());
				cycle.pop_back();
			}
		}
	}

	order.pop_back();
	color[u] = 2;
}

priority_queue<ii> pq;
int dist[maxn];

int solve(int u, int t) {
	for (int i = 0; i < n; ++i) dist[i] = inf;
	dist[u] = 0;
	pq.emplace(0, u);
	int ans = inf;
	while (!pq.empty()) {
		ii tp = pq.top(); pq.pop();
		if (-tp.fi > dist[tp.se]) continue;
		int u = tp.se;
		if (cost[u] >= t) {
			ans = min(ans, 2 * dist[u] + cost[u]);
		}
		for (auto [to, w] : gr[u]) {
			if (dist[u] + w < dist[to]) {
				dist[to] = dist[u] + w;
				pq.emplace(-dist[to], to);
			}
		}
	}
	return (ans == inf ? -1 : ans);
}

int a, b, w, t;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	
	cin >> n >> m;

	while (m--) {
		cin >> a >> b >> w, --a ,--b;
		gr[a].emplace_back(b, w);
		gr[b].emplace_back(a, w);
	}

	dfs(0, 0, 0);

	cin >> q;

	while (q--) {
		cin >> a >> t, --a;
		cout << solve(a, t) << '\n';
	}

	return 0;
}
