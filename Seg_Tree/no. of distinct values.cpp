// another/faster way to find no. of distinct values in a range 
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const int N = 5003;
const int MOD = 1e9 + 7;
ll or_query[N][N], a[N], n, k;
vector<ll> dp_before(N), cur_dp(N);
 
ll C(ll x, ll xx){
    return (or_query[x][xx]);
}
 
void compute(int l, int r, int tl, int tr){
    if(l > r)
        return;
    int mid = (l + r) >> 1;
    long long best = 0, idx;
    for(int i = tl; i <= min(mid, tr); ++i){
        if(dp_before[i - 1] + C(i, mid) > best){
            best = dp_before[i - 1] + C(i, mid);
            idx = i;
        }
    }
    cur_dp[mid] = best;
    compute(l, mid - 1, tl, idx);
    compute(mid + 1, r, idx, tr);
}
 
void solve(){
    cin >> n >> k;
    for(int i = 1; i <= n; ++i)
        cin >> a[i];
    for(int i = 1; i <= n; ++i){
        ll orr = 0;
        for(int j = i; j <= n; ++j){
            orr = (orr | a[j]);
            or_query[i][j] = orr;
        }
    }
    dp_before[0] = 0;
    for(int i = 1; i <= n; ++i)
        dp_before[i] = or_query[1][i];
    for(int j = 2; j <= k; ++j){
        compute(1, n, 1, n);
        dp_before = cur_dp;
    }
    cout << dp_before[n] << "\n";
}
 
int main(){
    fast;
    int t = 1;
    cin >> t;
    while(t--)
        solve();
    return 0;
}
