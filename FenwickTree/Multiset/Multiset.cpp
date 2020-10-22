/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Multiset
	Link: https://codeforces.com/contest/1354/problem/D
	Origin: Educational Codeforces Round 87 (Rated for Div. 2)
*/
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6+5;

int ft[maxn], n;

void add(int idx, int value) {
	for (; idx <= n; idx += (idx & -idx)) {
		ft[idx] += value;
	}
}

int query(int idx) {
	int rs = 0;
	for (; idx > 0; idx -= (idx & -idx)) {
		rs += ft[idx];
	}
	return rs;
}

int search(int k) {
	int sum = 0;
	int ans = 0;
	for (int i = 25; i >= 0; --i) {
		if (ans + (1 << i) <= n and sum + ft[ans + (1 << i)] < k) {
			sum += ft[ans + (1 << i)];
			ans += (1 << i);
		}
	}
	return ans + 1;
}

int q, x;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	cin >> n >> q;

	for (int i = 0; i < n; ++i) {
		cin >> x;
		add(x, 1);
	}

	for (int i = 0; i < q; ++i) {
		cin >> x;
		if (x < 0) {
			add(search(-x), -1);
		} else {
			add(x, 1);
		}
	}

	if (query(n) == 0) {
		cout << "0\n";
	} else {
		cout << search(1) << '\n';
	}

	return 0;
}