/*
	Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
	Problem: Help Leonardo!
	Link: https://www.urionlinejudge.com.br/judge/en/problems/view/2169
	Origin: Unknown
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
const int maxn = 15;
const int mod = 1e9+7;

string st;
int n, m, tot, s, q, c[maxn];
double p[maxn], dp[10010];
map<string, double> guns;
map<string, int> monsters;

int main() {
    fastIO();
    guns["HANDCANNON"] = 60.0;
    guns["RED9"] = 3.5;
    guns["MATILDA"] = 2.0;
    guns["STRIKER"] = 12.0;
    guns["HANDGUN"] = 2.0;
    guns["RIFLE"] = 12.0;
    guns["BLACKTAIL"] = 3.5;
    guns["TMP"] = 1.2;
    monsters["GANADOS"] = 50;
    monsters["COBRAS"] = 40;
    monsters["ZEALOT"] = 75;
    monsters["COLMILLOS"] = 60;
    monsters["GARRADOR"] = 125;
    monsters["LASPLAGAS"] = 100;
    monsters["GATLINGMAN"] = 150;
    monsters["REGENERATOR"] = 250;
    monsters["ELGIGANTE"] = 500;
    monsters["DR.SALVADOR"] = 350;
    while (cin >> n and n) {
    	for (int i = 0; i < n; ++i) {
    		cin >> st >> c[i];
    		p[i] = guns[st] * c[i];
    	}
    	cin >> m;
    	tot = 0;
    	while (m--) {
    		cin >> st >> q;
    		tot += monsters[st] * q;
    	}
    	cin >> s;
    	for (int i = 0; i <= s; ++i) dp[i] = 0.0;
    	for (int i = 0; i < n; ++i) {
    		for (int j = s; j >= c[i]; --j) {
    			dp[j] = max(dp[j], p[i] + dp[j-c[i]]);
    		}
    	}
    	if (dp[s] >= tot) {
    		cout << "Missao completada com sucesso\n\n";
    	} else {
    		cout << "You Are Dead\n\n";
    	}
    }
    return 0;
}

