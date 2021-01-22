#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;

const int K = 2;
const int SZ = 32;
const int mod = 1000000007;

namespace Trie {
	struct Vertex {
		int next[K];
		int val;
		Vertex () {
			fill(begin(next), end(next), -1);
			val = 0;
		}
	};

	vector<Vertex> trie(1);

	void add(int val) {
		int v = 0;
		for (int i = SZ-1; i >= 0; --i) {
			bool b = val & (1 << i);
			if (trie[v].next[b] == -1) {
				trie[v].next[b] = trie.size();
				trie.emplace_back();
			}
			v = trie[v].next[b];
		}
		trie[v].val = val;
	}
	int min_xor(int val) {
		int v = 0;
		for (int i = SZ-1; i >= 0; --i) {
			bool b = val & (1 << i);
			if (trie[v].next[b] != -1) {
				v = trie[v].next[b];
			} else if (trie[v].next[b^1] != -1) {
				v = trie[v].next[b^1];
			}
		}
		return trie[v].val;
	}
	int max_xor(int val) {
		int v = 0;
		for (int i = SZ-1; i >= 0; --i) {
			bool b = val & (1 << i);
			if (trie[v].next[b^1] != -1) {
				v = trie[v].next[b^1];
			} else if (trie[v].next[b] != -1) {
				v = trie[v].next[b];
			}
		}
		return val ^ trie[v].val;
	}
};

int n, q, dp[100010];
int x, rs;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	cin >> n;

	dp[0] = 1;
	for (int i = 0; i < n; ++i) {
		cin >> x;
		for (int j = 100000; j >= x; --j) {
			dp[j] = (dp[j] + dp[j-x]) % mod;
		}
	}

	for (int i = 1; i <= 100000; ++i) {
		if (dp[i] > 0) {
			Trie::add(i);
		}
	}

	cin >> q;

	while (q--) {
		cin >> x;
		rs = Trie::min_xor(x);
		cout << rs << ' ' << dp[rs] << '\n';
	}

	return 0;
}