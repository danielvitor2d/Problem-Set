/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Eyb0ss
	Link: https://codeforces.com/gym/101915/problem/L
	Origin: ACM International Collegiate Programming Contest, Tishreen Collegiate Programming Contest (2017)
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
const int maxn = 5e2+5;
const int mod = 1e9+7;

int tc;

int n;
i64 ans;
vvi ar;

i64 query(bool t) {
	i64 query_answer = 0LL;
	for (int r1 = 1; r1 <= n; ++r1) {
		vi col(n+1, (t ? inf : -inf));

		for (int r2 = r1; r2 <= n; ++r2) {
			for (int i = 1; i <= n; ++i) {
				if (t) col[i] = min(col[i], ar[r2][i]);
				else col[i] = max(col[i], ar[r2][i]);
			}

			vi left(n+1, 0), right(n+1, n+1);

			stack<int> st;
			for (int i = 1; i <= n; ++i) {
				while (!st.empty() and (t ? col[i] <= col[st.top()]: col[i] >= col[st.top()])) {
					right[st.top()] = i;
					st.pop();
				}
				st.push(i);
			}

			while (!st.empty()) st.pop();

			for (int i = n; i >= 1; --i) {
				while (!st.empty() and (t ? col[i] < col[st.top()]: col[i] > col[st.top()])) {
					left[st.top()] = i;
					st.pop();
				}
				st.push(i);
			}

			for (int i = 1; i <= n; ++i) {
				query_answer += 1LL * col[i] * (i - left[i]) * (right[i] - i);
			}
		}
	}
	return query_answer;
}

int main() {
	fastIO();
	cin >> tc;
	while (tc--) {
		cin >> n;
		ar = vvi(n+1, vi(n+1));

		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				cin >> ar[i][j];
			}
		}

		ans = query(0);
		ans -= query(1);

		cout << ans << '\n';
	}
	return 0;
}
