#include<bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define pb push_back
#define F first
#define S second
#define int long long
using namespace std;
const int N = 1e6 + 5, MOD = 1e9 + 7;
int n, fare[N], cost[N], q;

struct line{
    int m, c;
}a[N];

vector<line> cur, hull;

bool cmp(line x, line y){
    return (x.m >= y.m);
}

bool check(line a, line b, line cc){
    if(((b.c - a.c) * (a.m - cc.m)) > ((cc.c - a.c) * (a.m - b.m)))
        return true;
    return false;
}

void convex_hull(){
    hull.pb(cur[0]); // first line will always be in the hull
    if(n == 1)
        return;
    hull.pb(cur[1]); // assuming this line is also in the hull
    for(int j = 2; j < cur.size(); ++j){
        while(hull.size() > 1){
            line pre = hull.back(), par = hull[hull.size() - 2];
            if(check(par, pre, cur[j]))
                hull.pop_back();
            else
                break;
        }
        hull.pb(cur[j]);
    }
}

void solve(){
    cin >> n; //number of taxis
    for(int i = 0; i < n; ++i){
        cin >> cost[i] >> fare[i];
        a[i].m = cost[i];
        a[i].c = fare[i];
        // cost[i] is the cost per km
        // fare[i] is fixed if you take this taxi.
    }
    sort(a, a + n, cmp);
    cur.pb(a[0]);
    for(int i = 1; i < n; ++i){
        if(a[i].m != a[i - 1].m)
            cur.pb(a[i]);
        else{
            if(a[i].c < a[i - 1].c){
                cur.pop_back();
                cur.pb(a[i]);
            }
        }
    }
    convex_hull();
    cin >> q;
    while(q--){
        int x;
        cin >> x; // calc min cost to cover x kms
        int low = 0, high = (int) hull.size() - 2, ans = hull.size() - 1;
        while(low <= high){
            int mid = (low + high) / 2;
            if(hull[mid].m * x + hull[mid].c <= hull[mid + 1].m * x + hull[mid + 1].c){
                ans = mid;
                high = mid - 1;
            }
            else
                low = mid + 1;
        }

        cout << hull[ans].m * x + hull[ans].c << "\n";
    }
}

int32_t main(){
    fast;
    int t = 1;
    // cin >> t;
    while(t--)
        solve();
    return 0;
}
