#include <bits/stdc++.h>
using namespace std;

const int K = 26;

namespace Trie {
	struct Vertex {
		int next[K];
		int leaf;
		bool win, lose;
		Vertex () {
			fill(begin(next), end(next), -1);
			leaf = false;
			win = lose = false;
		}
	};

	inline int getId(char c) { return c-'a'; }

	vector<Vertex> trie;

	void build() {
		trie.clear();
		trie.emplace_back();
	}

	void add(string const &s) {
		int v = 0;
		for (char ch : s) {
			int c = getId(ch);
			if (trie[v].next[c] == -1) {
				trie[v].next[c] = trie.size();
				trie.emplace_back();
			}
			v = trie[v].next[c];
		}
		trie[v].leaf = true;
	}

	void get_ans(int v) {
		trie[v].lose = trie[v].leaf;
		trie[v].win = false;
		for (int c = 0; c < 26; ++c) {
			int to = trie[v].next[c];
			if (to != -1) {
				get_ans(to);
				trie[v].win |= !trie[to].win;
				trie[v].lose |= !trie[to].lose;
			}
		}
	}
	inline bool get_win(int v) {
		return trie[v].win;
	}
	inline bool get_lose(int v) {
		return trie[v].lose;
	}
};

int n, k;
string s;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	Trie::build();

	cin >> n >> k;

	for (int i = 0; i < n; ++i) {
		cin >> s;
		Trie::add(s);
	}

	Trie::get_ans(0);
	int win = Trie::get_win(0);
	int lose = Trie::get_lose(0);

	if (!win) {
		cout << "Second\n";
	} else if (lose) {
		cout << "First\n";
	} else {
		if (k & 1) cout << "First\n";
		else cout << "Second\n";
	}

	return 0;
}