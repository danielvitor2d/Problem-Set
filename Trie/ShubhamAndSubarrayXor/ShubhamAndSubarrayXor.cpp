#include <bits/stdc++.h>
using namespace std;

const int maxn = 950;
const int K = 2;
const int SZ = 32;

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
			} else {
				v = trie[v].next[b^1];
			}
		}
		return val ^ trie[v].val;
	}
	int max_xor(int val) {
		int v = 0;
		for (int i = SZ-1; i >= 0; --i) {
			bool b = val & (1 << i);
			if (trie[v].next[b^1] != -1) {
				v = trie[v].next[b^1];
			} else {
				v = trie[v].next[b];
			}
		}
		return val ^ trie[v].val;
	}
};

int n, v[maxn];
int sum, ans;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	cin >> n;

	for (int i = 1; i <= n; ++i) cin >> v[i];

	Trie::add(v[1]);
	for (int i = 2; i <= n; ++i) {
		sum = 0;
		for (int j = i; j <= n; ++j) {
			sum += v[j];
			ans = max(ans, Trie::max_xor(sum));
		}
		sum = 0;
		for (int j = i; j >= 1; --j) {
			sum += v[j];
			Trie::add(sum);
		}
	}

	cout << ans << '\n';

	return 0;
}