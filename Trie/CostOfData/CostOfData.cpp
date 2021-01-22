/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Cost of Data
	Link: https://www.hackerearth.com/practice/data-structures/advanced-data-structures/trie-keyword-tree/practice-problems/algorithm/cost-of-data-11/description/
	Origin: HackerEarth
*/
#include <bits/stdc++.h>
using namespace std;

const int K = 26;

namespace Trie {
	struct Vertex {
		int next[K];
		int leaf;
		int count;
		Vertex () {
			fill(begin(next), end(next), -1);
			leaf = count = 0;
		}
	};

	inline int getId(char c) { return c-'a'; }

	vector<Vertex> trie(1);

	int add(string const &s) {
		int ans = 0;
		int v = 0;
		++trie[v].count;
		for (char ch : s) {
			int c = getId(ch);
			if (trie[v].next[c] == -1) {
				++ans;
				trie[v].next[c] = trie.size();
				trie.emplace_back();
			}
			v = trie[v].next[c];
			++trie[v].count;
		}
		++trie[v].leaf;
		return ans;
	}
	int countStr(string const &s) {
		int v = 0;
		for (char ch : s) {
			int c = getId(ch);
			if (trie[v].next[c] == -1) return 0;
			v = trie[v].next[c]; 
		}
		return trie[v].leaf;
	}
	int countPre(string const &s) {
		int v = 0;
		for (char ch : s) {
			int c = getId(ch);
			if (trie[v].next[c] == -1) return 0;
			v = trie[v].next[c];
		}
		return trie[v].count;
	}
	bool remove(string const &s) {
		vector<int> rm;
		int v = 0;
		rm.push_back(v);
		for (char ch : s) {
			int c = getId(ch);
			if (trie[v].next[c] == -1) return false;
			v = trie[v].next[c];
			rm.push_back(v); 
		}
		if (trie[v].leaf > 0) {
			--trie[v].leaf;
			for (int x : rm) --trie[x].count;
			return true;
		}
		return false;
	}
};

int n, ans;
string s;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	cin >> n;

	while (n--) {
		cin >> s;
		ans += Trie::add(s);
	}

	cout << 1+ans << '\n';

	return 0;
}