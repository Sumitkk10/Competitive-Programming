// Edmonds-Karp impl of Ford-Fulkerson algorithm
// Time complexity to find max flow is O(E^2 * V)

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define int long long
#define F first
#define S second
#define pb push_back
using namespace std;
const int N = 1e6 + 5, MOD = 1e9 + 7;
int n, m;
pair<int, int> par[N];
vector<pair<int, int> > g[N];
vector<int> edges;

int bfs(int source, int sink){
    for(int i = 1; i <= n; ++i)
        par[i] = {-1, -1};
    queue<pair<int, int> > q;
    q.push({source, 1e16});
    par[source].S = 1;
    while(!q.empty()){
        pair<int, int> cur = q.front();
        q.pop();
        for(auto k : g[cur.F]){
            if(par[k.F].S == -1 and edges[k.S] > 0){
                par[k.F].F = k.S;
                par[k.F].S = cur.F;
                int temp = min(cur.S, edges[k.S]);
                if(k.F == sink)
                    return temp;
                q.push({k.F, temp});
            }
        }
    }
    return 0;
}

void solve(){
    cin >> n >> m;
    for(int i = 0; i < m; ++i){
        int u, v, c;
        cin >> u >> v >> c;
        g[u].pb({v, i});
        g[v].pb({u, i + m});
        edges.pb(c);
    }
    for(int i = m; i <= 2*m; ++i)
        edges.pb(0);
    int ans = 0, s = 1, t = n;
    while(true){
        int flow = bfs(s, t);
        if(!flow)
            break;
        ans += flow;
        int cur = t;
        while(cur != s){
            edges[par[cur].F] -= flow;
            if(par[cur].F < m)
                edges[par[cur].F + m] += flow;
            else
                edges[par[cur].F - m] += flow;
            cur = par[cur].S;
        }
    }
    cout << ans << "\n";
}

int32_t main(){
    fast;
    int t = 1;
    // cin >> t;
    while(t--)
        solve();
    return 0;
}
