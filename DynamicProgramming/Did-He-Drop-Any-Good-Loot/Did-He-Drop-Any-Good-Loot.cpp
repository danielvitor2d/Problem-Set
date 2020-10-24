/*
    Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
    Problem: Did he drop any good loot?
    Link: https://codeforces.com/gym/100694/problem/A
    Origin: 2015, VIII Samara Regional Intercollegiate Programming Contest
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int INF = 0x3f3f3f3f;
const int N = 1e4 + 5;

struct Item {
	int price, wei, power;
	bool operator < (const Item other) const {
		return power > other.power;
	}
};

int n, m;
Item v[N];
bool seen[N][710][3];
ll dp[N][710][3];

ll solve(int idx, int weigth, int used) {
	if (idx == n + 1) return 0;
	
	if (seen[idx][weigth][used]) return dp[idx][weigth][used];
	seen[idx][weigth][used] = true;
	
	ll ans = solve(idx + 1, weigth, used);
	
	if (v[idx].wei <= weigth + v[idx].power && used < 2) {
		ans = max(ans, v[idx].price + 
		solve(idx + 1, weigth + v[idx].power - v[idx].wei, used + 1));
	}

	if (v[idx].wei <= weigth) {
		ans = max(ans, v[idx].price + 
				  solve(idx + 1, weigth - v[idx].wei, used));
	}
	
	return dp[idx][weigth][used] = ans;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		cin >> v[i].price >> v[i].wei >> v[i].power;
	sort(v+1, v+1+n);
	cout << solve(1, m, 0) << "\n";
	
	return 0;
}