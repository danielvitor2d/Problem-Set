/*
    Author: [UFC-QXD] Daniel Vitor Pereira Rodrigues <danielvitor@alu.ufc.br>
    Problem: Frequency
    Link: https://neps.academy/problem/498, https://www.urionlinejudge.com.br/judge/pt/problems/view/2467
    Origin: OBI 2014 - Second Phase - Level 2
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
const int maxn = 3e5+50;
const int mod = 1e9+7;
 
struct FT {
    int ft[maxn];
    void add(int idx, int value) {
        for (; idx < maxn; idx += (idx & -idx)) {
            ft[idx] += value;
        }
    }
    int query(int idx) {
        int rs = 0;
        for (; idx > 0; idx -= (idx & -idx)) {
            rs += ft[idx];
        }
        return rs;
    }
    int query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l-1);
    }
};
 
FT cores[2][51];
ii last[2][maxn];
 
int n, q;
int op, x, r;
 
int main() {
    fastIO();
    
    cin >> n >> q;
 
    for (int i = 1; i <= n; ++i) {
        cores[0][0].add(i, 1);
        last[0][i] = {i, 0};
    }
 
    for (int i = n+1; i <= n+n; ++i) {
        cores[1][0].add(i, 1);
        last[1][i-n] = {i, 0};
    }
 
    for (int t = n+n+1; t <= n+n+q; ++t) {
        cin >> op;
        if (op == 1) {
            cin >> x >> r;
            
            cores[0][ last[0][x].se ].add(last[0][x].fi, -1);
 
            cores[0][r].add(t, 1);
            last[0][x] = {t, r};
 
        } else if (op == 2) {
            cin >> x >> r;
            
            cores[1][ last[1][x].se ].add(last[1][x].fi, -1);
 
            cores[1][r].add(t, 1);
            last[1][x] = {t, r};
 
        } else if (op == 3) {
            cin >> x;
 
            int ans = -1, mx = 0, sum = 0;
            for (int i = 50; i >= 0; --i) {
                if (last[0][x].se == i) continue;
                int rs = cores[1][i].query(last[0][x].fi + 1, n+n+q);
                sum += rs;
                if (rs > mx) {
                    mx = rs;
                    ans = i;
                }
            }
 
            if (n-sum > mx or (n-sum == mx and last[0][x].se > ans) or ans == -1) ans = last[0][x].se;
            cout << ans << '\n';
        } else if (op == 4) {
            cin >> x;
 
            int ans = -1, mx = 0, sum = 0;
            for (int i = 50; i >= 0; --i) {
                if (last[1][x].se == i) continue;
                int rs = cores[0][i].query(last[1][x].fi + 1, n+n+q);
                sum += rs;
                if (rs > mx) {
                    mx = rs;
                    ans = i;
                }
            }
 
            if (n-sum > mx or (n-sum == mx and last[1][x].se > ans) or ans == -1) ans = last[1][x].se;
            cout << ans << '\n';
        }
    }   
 
    return 0;
}