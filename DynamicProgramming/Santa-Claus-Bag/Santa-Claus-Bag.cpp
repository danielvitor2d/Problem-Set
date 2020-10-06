/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Santa Claus Bag
	Link: https://www.urionlinejudge.com.br/judge/en/problems/view/1767
	Origin: Christmas Contest 2014
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
const int maxn = 1e3+5;
const int mod = 1e9+7;

struct bag {
	int v, p, qtd;
	bool operator > (bag oth) const {
		return qtd > oth.qtd;
	}
	bag () {
		v = p = qtd = 0;
	}
};

int tc, n;
int c[maxn], p[maxn];
bag dp[maxn];

int main() {
    fastIO();
    cin >> tc;
    while (tc--) {
    	cin >> n;

    	for (int i = 0; i < n; ++i) {
    		cin >> p[i] >> c[i];
    	}

    	for (int i = 0; i <= 50; ++i) dp[i] = bag();

    	for (int i = 0; i < n; ++i) {
    		for (int j = 50; j >= c[i]; --j) {
    			bag new_bag = dp[j-c[i]];
    			new_bag.qtd += p[i];
    			new_bag.p += c[i];
    			++new_bag.v;
    			if (new_bag > dp[j]) dp[j] = new_bag;
    		}
    	}

    	for (int i = 50; i > 0; --i) {
    		if (dp[i].qtd > 0) {
    			cout << dp[i].qtd << " brinquedos\n";
    			cout << "Peso: " << dp[i].p << " kg\n";
    			cout << "sobra(m) " << n-dp[i].v << " pacote(s)\n\n";
    			break;
    		}
    	}

    }
    return 0;
}

