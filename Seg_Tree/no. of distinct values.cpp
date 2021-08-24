// another/faster way to find no. of distinct values in a range 

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const int N = 1e6 + 5;
const int MOD = 1e9 + 7;
int n, k, a[N], nxt[N], l = 1, r, distinct, mp[N];
vector<ll> cur_dp(N), dp_before(N);

void cost(int i, int j){
    while(l > i){
        --l;
        if(!mp[a[l]]) ++distinct;
        mp[a[l]]++;
    }
    while(l < i){
        if(mp[a[l]] == 1) --distinct;
        mp[a[l]]--;
        ++l;
    }
    while(r > j){
        if(mp[a[r]] == 1) --distinct;
        mp[a[r]]--;
        --r;
    }
    while(r < j){
        ++r;
        if(!mp[a[r]]) ++distinct;
        mp[a[r]]++;
    }
}

void dnc(int l, int r, int optl, int optr){
    if(l > r) return;
    int mid = (l + r) >> 1;
    ll mx = 0, idx;
    for(int i = optl; i < min(mid, optr + 1); ++i){
        cost(i + 1, mid);
        if(mx < dp_before[i] + distinct){
            mx = dp_before[i] + distinct;
            idx = i;
        }
    }
    cur_dp[mid] = mx;
    dnc(l, mid - 1, optl, idx);
    dnc(mid + 1, r, idx, optr);
}

void solve(){
    cin >> n >> k;
    for(int i = 1; i <= n; ++i)
        cin >> a[i];
    // let dp[i][k] be the max cost in prefix of i with exactly k groups.
    // cost(j + 1, i) is no. of distinct values in (j + 1, i)
    // we use d&c dp to caluclate.
    for(int i = 1; i <= n; ++i)
        dp_before[i] = 0;
    for(int j = 1; j <= k; ++j){
        dnc(1, n, 0, n);
        dp_before = cur_dp;
    }
    cout << dp_before[n] << "\n";
}

int main(){
    fast;
    int t = 1;
    // cin >> t;
    while(t--)
        solve();
    return 0;
}
