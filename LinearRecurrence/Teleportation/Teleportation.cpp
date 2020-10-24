/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Teleportation
	Link: https://www.urionlinejudge.com.br/judge/pt/problems/view/1713
	Origin: SBC 2014 Programming Marathon
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

const double eps = 1e-9;

#define eq(a, b) (abs(a - b) < eps)
#define lt(a, b) ((a + eps) < b)
#define gt(a, b) (a > (b + eps))
#define le(a, b) (a < (b + eps))
#define ge(a, b) ((a + eps) > b)

#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define ms(a, x) memset(a, x, sizeof(a))
#define len(x) (int)(x).size()
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

const int dtx[] = { 0, 0, -1, 1, 1, -1,  1, -1};
const int dty[] = {-1, 1,  0, 0, 1, -1, -1,  1};
const int dtxc[] = {1,  1, 2,  2, -1, -1, -2, -2};
const int dtyc[] = {2, -2, 1, -1,  2, -2,  1, -1};

const double pi = acos(-1.0);
const int inf = 0x3f3f3f3f;
const int maxn = 1e5+5;
const int mod = 10000;

const int D = 100;

int tam;

struct M {
	int m[D][D];

	int* operator[](int i) {
		return m[i];
	}

	M operator*(M oth) {
		M res;
		for (int i = 0; i < tam; ++i) {
			for (int j = 0; j < tam; ++j) {
				res[i][j] = 0;
				for (int k = 0; k < tam; ++k) {
					res[i][j] = (res[i][j] + m[i][k] * oth[k][j] % mod + mod) % mod;
				}
			}
		}
		return res;
	}	

	M exp(int e) {
		M res;
		for (int i = 0; i < tam; ++i)
			for (int j = 0; j < tam; ++j)
				res[i][j] = (i==j);
		M base = *this;
		while (e > 0) {
			if (e & 1LL) res = res * base;
			base = base * base;
			e >>= 1LL;
		}
		return res;
	}
};

int l, s, t;
int a, b, c, d;
M adj;

int main() {
	fastIO();
	
	cin >> tam >> l;
	cin >> s >> t, --s, --t;

	for (int i = 0; i < tam; ++i) {
		cin >> a >> b >> c >> d, --a, --b, --c, --d;
		++adj[i][a];
		++adj[i][b];
		++adj[i][c];
		++adj[i][d];
	}

	adj = adj.exp(l);

	cout << adj[s][t] << '\n';

	return 0;
}