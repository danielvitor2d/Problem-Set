/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Range Set Query
	Link: https://atcoder.jp/contests/abc174/tasks/abc174_f
	Origin: AtCoder Beginner Contest 174
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
#define len(x) (x).size()
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
const int maxn = 5e5+5;
const int mod = 1e9+7;

const int BLOCK_SIZE = 800;

int v[maxn], f[maxn];
int ans;

void remove(int idx) {
	--f[v[idx]];
	if (f[v[idx]] == 0) --ans;
}

void add(int idx) {
	++f[v[idx]];
	if (f[v[idx]] == 1) ++ans;
}

int get_answer() {
	return ans;
}

struct Query {
	int l, r, idx;
	bool operator < (const Query oth) const {
		if (l / BLOCK_SIZE != oth.l / BLOCK_SIZE) return l < oth.l;
		return (l / BLOCK_SIZE & 1) ? (r < oth.r) : (r > oth.r); 
	}
};

vi mo_s_algorithm(vector<Query> queries) {
	vi answers(queries.size());
	sort(queries.begin(), queries.end());
	int l = 0, r = 0;
	for (Query q : queries) {
		while (q.l < l) add(--l);
		while (r < q.r) add(++r);
		while (l < q.l) remove(l++);
		while (q.r < r) remove(r--);
		answers[q.idx] = get_answer();
	}
	return answers;
}

vector<Query> queries;
int n, q, l, r;

int main() {
	fastIO();
	
	cin >> n >> q;

	queries = vector<Query>(q);

	for (int i = 1; i <= n; ++i) {
		cin >> v[i];
	}

	for (int i = 0; i < q; ++i) {
		cin >> queries[i].l >> queries[i].r;
		queries[i].idx = i;
	}

	vi ans = mo_s_algorithm(queries);

	for (int x : ans) {
		cout << x << '\n';
	}

	return 0;
}
