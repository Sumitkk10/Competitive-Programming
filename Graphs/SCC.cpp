/*
this is a code to find SCC as well as to create an condensation graph.
*/

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const int N = 100002;
vector<int> graph[N], transpose[N], condensation[N], order, scc;
int component[N], cur, ans = INT_MAX, n, m, siz[N];
bool vis[N];

void dfs(int node){
    vis[node] = true;
    for(auto k : graph[node])
        if(!vis[k])
            dfs(k);
    order.push_back(node);
}


void dfs1(int node){
    vis[node] = true;
    scc.push_back(node);
    for(auto k : transpose[node])
        if(!vis[k])
            dfs1(k);
}

void dfs2(int node){
    cur += siz[node];
    for(auto k : condensation[node])
        dfs2(k);
}

void solve(){
    cin >> n >> m;
    for(int i = 1; i <= m; ++i){
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        transpose[v].push_back(u);
    }
    for(int i = 1; i <= n; ++i)
        if(!vis[i])
            dfs(i);
    reverse(order.begin(), order.end());
    memset(vis, 0, sizeof vis);
    for(auto k : order){
        if(vis[k]) continue;
        dfs1(k);
        // from here we are actually building condensation graph.
        for(int i = 0; i < scc.size(); ++i)
            component[scc[i]] = scc[0];
        siz[scc[0]] = scc.size();
        scc.clear();
    }
    for(int i = 1; i <= n; ++i){
        for(auto k : graph[i]){
            int par = component[i], par1 = component[k];
            if(par != par1)
                condensation[par].push_back(par1);
        }
    }
    for(int i = 1; i <= n; ++i){
        int par = component[i];
        dfs2(par);
        ans = min(ans, cur);
        cur = 0;
    }
    cout << ans << "\n";
}

int main(){
    fast;
    int t = 1;
    // cin >> t;
    while(t--)
        solve();
    return 0;
}
