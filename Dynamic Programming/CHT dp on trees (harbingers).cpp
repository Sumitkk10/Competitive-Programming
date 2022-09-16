#include<bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define pb push_back
#define F first
#define S second
#define int long long
using namespace std;
const int N = 1e5 + 5, MOD = 1e9 + 7;
vector<pair<int, int> > g[N];
int n, par[N], dis[N], dp[N], s[N], d[N];

struct Line{
    int m, c;
 
    int val(int x){
        return m*x + c;
    }
};

Line hulls[N];
int cur_hullsize = 1;

bool check(Line a, Line b, Line cc){
    __int128 x = (b.c - a.c);
    x = x * (a.m - cc.m);
    __int128 y = (cc.c - a.c);
    y = y * (a.m - b.m);
    if(x > y)
        return true;
    return false;
}

int pos(int mm, int cc){
    Line cur;
    cur.m = mm;
    cur.c = cc;
    if(cur_hullsize < 2 or !(check(hulls[cur_hullsize - 2], hulls[cur_hullsize - 1], cur)))
        return cur_hullsize;
    int low = 1, high = cur_hullsize - 1, ans = 0;
    while(low <= high){
        int mid = (low + high) / 2;
        if(check(hulls[mid - 1], hulls[mid], cur)){
            ans = mid;
            high = mid - 1;
        }
        else
            low = mid + 1;
    }
    return ans;
}

int get(int x){
    int low = 0, high = cur_hullsize - 1;
    while(low < high){
        int mid = (low + high) / 2;
        if(hulls[mid].val(x) < hulls[mid + 1].val(x))
            high = mid;
        else
            low = mid + 1;
    }
    return hulls[high].val(x);
}
 
void dfs(int node, int p, int sum){
    dis[node] = sum;
    par[node] = p;
    for(auto k : g[node]){
        if(k.F == p) continue;
        dfs(k.F, node, sum + k.S);
    }
}

/*
we want to find the position in the convex hull where the current line will go
we will replace that position with the current line
we will change it back once I go up from that node
*/

void dfs1(int node){
    dp[node] = get(d[node]) + s[node] + dis[node] * d[node];
    int cur, here = cur_hullsize;
    Line pre;
    if(node != 1){
        cur = cur_hullsize = pos(-dis[node], dp[node]);
        Line neww;
        neww.m = -dis[node];
        neww.c = dp[node];
        pre = hulls[cur];
        hulls[cur] = neww;
        cur_hullsize++;
    }
    for(auto k : g[node]){
        if(k.F == par[node]) 
            continue;
        dfs1(k.F);
    }
    if(node != 1){
        cur_hullsize = here;
        hulls[cur] = pre;
    }
}

void solve(){
    cin >> n;
    for(int i = 1; i < n; ++i){
        int u, v, c;
        cin >> u >> v >> c;
        g[u].pb({v, c});
        g[v].pb({u, c});
    }
    for(int i = 1; i < n; ++i)
        cin >> s[i + 1] >> d[i + 1];
    dfs(1, 0, 0);
    Line wut;
    wut.m = 0, wut.c = 0;
    hulls[0] = wut;
    dfs1(1);
    for(int i = 2; i <= n; ++i)
        cout << dp[i] << " ";
}
 
int32_t main(){
    fast;
    int t = 1;
    // cin >> t;
    while(t--)
        solve();
    return 0;
}
