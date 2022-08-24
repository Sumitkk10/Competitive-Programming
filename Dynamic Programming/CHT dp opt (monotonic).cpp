/*
CHT dp optimisation can be applied when : 
dp[i] = min/max(dp[i], dp[j] + C(j...i));

where C(j + 1..i) can be written as mx + c
like C(j..i) = pre[j] * pre[i] + dp[j]

To find maximums, gradients must be sorted in increasing order.
To find minimums, gradients must be sorted in decreasing order.

*/
#include<bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define pb push_back
#define F first
#define S second
#define int long long
using namespace std;
const int N = 1e6 + 5, MOD = 1e9 + 7;
int n, a, b, c, x[N], p[N], dp[N];

struct line{
    int m, c;
};
vector<line> hull;

long double intersection(line x, line y){
    long double p = y.c - x.c;
    long double q = x.m - y.m;
    return (long double) p / q;
}

void add(int x, int y){
    line cur;
    cur.m = x;
    cur.c = y;
    while(hull.size() > 1){
        line pre = hull.back(), par = hull[hull.size() - 2];
        if(intersection(cur, par) <= intersection(pre, par))
            hull.pop_back();
        else
            break;
    }
    hull.pb(cur);
}

int get(int x){
    int low = 0, high = (int) hull.size() - 2, ans = hull.size() - 1;
    while(low <= high){
        int mid = (low + high) / 2;
        if(hull[mid].m * x + hull[mid].c >= hull[mid + 1].m * x + hull[mid + 1].c){
            ans = mid;
            high = mid - 1;
        }
        else
            low = mid + 1;
    }
    return hull[ans].m * x + hull[ans].c;
}

void solve(){
    cin >> n >> a >> b >> c;
    for(int i = 1; i <= n; ++i){
        cin >> x[i];
        p[i] = p[i - 1] + x[i];
    }
    line zero;
    zero.m = 0, zero.c = 0;
    hull.pb(zero);
    for(int i = 1; i <= n; ++i){
        int temp = a*p[i]*p[i] + b*p[i] + c;
        dp[i] = temp + get(p[i]);
        add(-2*a*p[i], dp[i] + a*p[i]*p[i] - b*p[i]);
    }
    cout << dp[n] << "\n";
}

int32_t main(){
    fast;
    int t = 1;
    // cin >> t;
    while(t--)
        solve();
    return 0;
}
