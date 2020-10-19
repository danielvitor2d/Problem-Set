/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Tug of War
	Link: https://www.urionlinejudge.com.br/judge/pt/problems/view/1586
	Origin: Heating for OBI 2014
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

const int maxn = 1e5+5;

int n;
i64 a[maxn];
string v[maxn];

i64 psa1[maxn], ips1[maxn];
i64 psa2[maxn], ips2[maxn];
i64 sum1, sum2;

int lo, hi, best, ans;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	while (cin >> n and n) {
		for (int i = 1; i <= n; ++i) {
			cin >> v[i];
			a[i] = 0;
			for (char &c : v[i]) {
				a[i] += c;
			}
			psa1[i] = psa1[i-1] + a[i];
			ips1[i] = ips1[i-1] + i * a[i];
		}
		psa2[n+1] = 0;
		ips2[n+1] = 0;
		for (int i = n; i >= 1; --i) {
			psa2[i] = psa2[i+1] + a[i];
			ips2[i] = ips2[i+1] + (n - i + 1) * a[i];
		}
		lo = 1, hi = n, ans = -1;
		while (lo <= hi) {
			best = (lo + hi)/2;
			sum1 = ips2[1] - ips2[best+1] - (n-best)*(psa2[1] - psa2[best+1]);
			sum2 = ips1[n] - ips1[best] - (best)*(psa1[n] - psa1[best]);
			if (sum1 == sum2) {
				ans = best;
				break;
			} else if (sum1 < sum2) {
				lo = best + 1;
			} else {
				hi = best - 1;
			}
		}
		if (ans == -1) cout << "Impossibilidade de empate.\n";
		else cout << v[ans] << '\n';
	}

	return 0;
}