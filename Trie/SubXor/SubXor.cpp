#include <bits/stdc++.h>
using namespace std;
using i64 = long long int;

const int K = 2;
const int SZ = 32;

namespace Trie {
	struct Vertex {
		int next[K];
		int val, pre;
		Vertex () {
			fill(begin(next), end(next), -1);
			val = 0;
			pre = 0;
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
			++trie[v].pre;
		}
		trie[v].val = val;
	}

	i64 count(int v, int val, int k, int bit) {
		if (v == -1 or bit < 0) return 0LL;
		i64 ans = 0LL;
		bool p = (1 << bit) & val, b = (1 << bit) & k;
		if (p and b) {
			if (trie[v].next[1] != -1) ans += trie[trie[v].next[1]].pre;
			ans += count(trie[v].next[0], val, k, bit-1);
		} else if (!p and b) {
			if (trie[v].next[0] != -1) ans += trie[trie[v].next[0]].pre;
			ans += count(trie[v].next[1], val, k, bit-1);
		} else if (p and !b) {
			ans += count(trie[v].next[1], val, k, bit-1);
		} else {
			ans += count(trie[v].next[0], val, k, bit-1);
		}
		return ans;
	}

	i64 get_ans(int val, int k)	{
		return count(0, val, k, 31);
	}
};

int tc, n, k, x, psa;
i64 ans;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> tc;
	while (tc--) {
		cin >> n >> k;
		ans = 0LL;
		psa = 0;
		Trie::build();
		Trie::add(0);
		for (int i = 0; i < n; ++i) {
			cin >> x;
			psa ^= x;
			ans += Trie::get_ans(psa, k);
			Trie::add(psa);
		}
		cout << ans << '\n';
	}
	return 0;
}