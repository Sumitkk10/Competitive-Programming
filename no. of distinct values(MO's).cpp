/*
Mo's algo to find no. of distinct values in a range
*/

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const int N = 1e6 + 5;
const int MOD = 1e9 + 7;
int n, k, a[N], l = 1, r, distinct, mp[N], sz = sqrt(N);

struct st{
    int L, R, i;
};

bool cmp(st a, st b){
    if(a.L/sz == b.L/sz)
        return a.R < b.R;
    return a.L < b.L;
}

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

void solve(){
    cin >> n;
    for(int i = 1; i <= n; ++i)
        cin >> a[i];
    int q;
    cin >> q;
    st qq[q];
    for(int i = 0; i < q; ++i){
        cin >> qq[i].L >> qq[i].R;
        qq[i].i = i;
        qq[i].L, qq[i].R;
    }
    vector<int> ans(q);
    sort(qq, qq + q, cmp);
    for(int i = 0; i < q; ++i){
        cost(qq[i].L, qq[i].R);
        ans[qq[i].i] = distinct;
    }
    for(auto k : ans) cout << k << "\n";
}

int main(){
    fast;
    int t = 1;
    // cin >> t;
    while(t--)
        solve();
    return 0;
}
