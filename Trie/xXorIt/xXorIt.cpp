#include <bits/stdc++.h>
using namespace std;

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

	vector<Vertex> trie;

	void build() {
		trie.clear();
		trie.emplace_back();
	}

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

int tc;
int n, x, a, psa;
int answer, mx;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> tc;
	while (tc--) {
		answer = 0;
		mx = 0;
		psa = 0;

		cin >> n >> x;

		Trie::build();
		Trie::add(0);

		for (int i = 0; i < n; ++i) {
			cin >> a;
			psa ^= a;
			int rs = Trie::max_xor(psa^x);
			Trie::add(psa);
			if (rs > mx) {
				mx = rs;
				answer = rs^x;
			}
		}

		cout << answer << '\n';
	}
	return 0;
}