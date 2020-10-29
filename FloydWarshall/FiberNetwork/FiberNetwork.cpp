/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Fiber Network
	Link: https://www.urionlinejudge.com.br/judge/pt/problems/view/1738
	Origin: University of Ulm local Contest 2001/2002.
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
typedef pair<int, int> ii;
typedef pair<i64, i64> ll;
typedef vector<int> vi;
typedef vector<i64> vi64;
typedef vector<ii> vii;
typedef vector<ll> vll;
typedef vector<vi> vvi;

#define fastio ios_base::sync_with_stdio(0), cin.tie(0)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define ms(a, x) memset(a, x, sizeof(a))
#define len(x) (int)(x).size()
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

const double eps = 1e-9;
const double pi = acos(-1.0);
const int inf = 0x3f3f3f3f;
const int maxn = 2e2+5;
const int mod = 1e9+7;

int n;
int gr[26][maxn][maxn];
int a, b;
string s;

int main() {
	fastio;
	
	while (cin >> n and n) {

		for (int k = 0; k < 26; ++k) {
			for (int i = 0; i <= n; ++i) {
				for (int j = 0; j <= n; ++j) {
					gr[k][i][j] = (i != j) * inf;
				}
			}
		}

		while (cin >> a >> b and a) {
			cin >> s;
			for (char c : s) {
				gr[c-'a'][a][b] = 1;
			}
		}

		for (int c = 0; c < 26; ++c) {
			for (int k = 1; k <= n; ++k) {
				for (int i = 1; i <= n; ++i) {
					for (int j = 1; j <= n; ++j) {
						gr[c][i][j] = min(gr[c][i][j], gr[c][i][k] + gr[c][k][j]);
					}
				}
			}
		}

		while (cin >> a >> b and a) {
			s.clear();
			for (int c = 0; c < 26; ++c) {
				if (gr[c][a][b] != inf) {
					s += (c+'a');
				}
			}
			if (s.empty()) cout << "-\n";
			else cout << s << '\n';
		}
		cout << '\n';
	}

	return 0;
}
