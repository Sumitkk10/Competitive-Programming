// Solution for Guards : https://dunjudge.me/analysis/problems/894/

/*
we can use divide and conquer dp optimization when we have a recurrence as following : 
dp[i] = min(a[j] + C(j..i)) for all j < i
dp[i][j] = min(dp[k][j - 1] + C(k..i)) for all k < i

observe that opt[i] will be monotonic, opt[i] <= opt[i + 1]
then we can use d&c optimization. :)
*/

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const int N = 8005;
const int MOD = 1e9 + 7;
long long  n, k, a[N], pre_sum[N];
vector<ll> dp_b4(N), cur_dp(N);

long long C(ll x, ll xx){
    if(xx < x) return LLONG_MAX;
    ll ans = ((xx - x)*(pre_sum[xx] - pre_sum[x]));
    return ans;
}

void compute(int l, int r, int optl, int optr) {
    if (l > r)
        return;
    int mid = (l + r) >> 1;
    long long best = LLONG_MAX, idx;
    for (int i = optl; i <= min(mid, optr); i++) {
        if(i == mid) continue;
        if(best > dp_b4[i] + C(i, mid)){
            best = dp_b4[i] + C(i, mid);
            idx = i;
        }
    }
    cur_dp[mid] = best;
    compute(l, mid - 1, optl, idx);
    compute(mid + 1, r, idx, optr);
}

void solve(){
    cin >> n >> k;
    for(int i = 1; i <= n; ++i){
        cin >> a[i];
        pre_sum[i] = pre_sum[i - 1] + a[i];
    }
    // if we make k groups in the prefix of i.
    for(int i = 1; i <= n; ++i)
        dp_b4[i] = C(0, i);
    for(int j = 2; j <= k; ++j){
        compute(1, n, 0, n - 1);
        dp_b4 = cur_dp;
    }
    cout << dp_b4[n] << "\n";
}

int main(){
    fast;
    int t = 1;
    // cin >> t;
    while(t--)
        solve();
    return 0;
}
