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
		return val ^ trie[v].val;
	}
	int max_xor(int val) {
		int v = 0;
		for (int i = SZ-1; i >= 0; --i) {
			bool b = val & (1 << i);
			if (trie[v].next[b^1] != -1) {
				v = trie[v].next[b^1];
			} else {
				v = trie[v].next[b^1];
			}
		}
		return val ^ trie[v].val;
	}
};

int q, op, x;
int aux;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	Trie::add(0);

	cin >> q;

	while (q--) {
		cin >> op;
		if (op == 1) {
			cin >> x;
			Trie::add(x^aux);
		} else if (op == 2) {
			cin >> x;
			aux ^= x;
		} else if (op == 3) {
			cout << Trie::min_xor(aux) << '\n';
		}
	}

	return 0;
}