// dinic's with scaling, taken from kactl
// time complexity for max bipartite matching: O(E * sqrt(V))
// general complexity for flow problems: O(V*V*E), but with scaling here it is O(V*E*log(U)) where U is the max flow

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define int long long
#define F first
#define S second
#define pb push_back

using namespace std;

using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vii = vector<pii>;
using vvii = vector<vii>;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(s) s.begin(), s.end()
#define sz(x) (int)(x).size()
const int N = 1e5 + 5, MOD = 1e9 + 7;

struct Dinic {
    struct Edge {
        int to, rev;
        int c, oc;
        int flow() { return max(oc - c, 0ll); } // if you need flows
    };
    vi lvl, ptr, q;
    vector<vector<Edge>> adj;
    Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
    void addEdge(int a, int b, int c, int rcap = 0) {
        adj[a].push_back({b, sz(adj[b]), c, c});
        adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
    }
    int dfs(int v, int t, int f) {
        if (v == t || !f) return f;
        for (int& i = ptr[v]; i < sz(adj[v]); i++) {
            Edge& e = adj[v][i];
            if (lvl[e.to] == lvl[v] + 1)
                if (int p = dfs(e.to, t, min(f, e.c))) {
                    e.c -= p, adj[e.to][e.rev].c += p;
                    return p;
                }
        }
        return 0;
    }
    int calc(int s, int t) {
        int flow = 0; q[0] = s;
        rep(L,0,31) do { // 'int L=30' maybe faster for random data
            lvl = ptr = vi(sz(q));
            int qi = 0, qe = lvl[s] = 1;
            while (qi < qe && !lvl[t]) {
                int v = q[qi++];
                for (Edge e : adj[v])
                    if (!lvl[e.to] && e.c >> (30 - L))
                        q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
            }
            while (int p = dfs(s, t, 1e18)) flow += p;
        } while (lvl[t]);
        return flow;
    }
    bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

void solve(){
    int n, m; cin >> n >> m;
    int p, q; cin >> p >> q;
    vector<string> a(n); for(auto &x : a) cin >> x;
 
    int tot = 0;
    for(auto &row : a) for(auto &cell : row) tot += (cell == '1');
 
    if(p >= 2*q){
        cout << 1ll*tot*p << '\n';
        return;
    }   
 
    vi dy = {-1, 0, 1, 0};
    vi dx = {0, 1, 0, -1};

    Dinic network(n*m + 2);
    
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            if(a[i][j] == '1'){
                if((i + j) & 1){
                    network.addEdge(i * m + j + 1, n * m + 1, 1);
                    continue;
                     
                }
                else
                    network.addEdge(0, i * m + j + 1, 1);
                for(int k = 0; k < 4; ++k){
                    int _i = i + dy[k], _j = j + dx[k];
                    if(_i < 0 or _j < 0 or _i >= n or _j >= m) continue;
                    if(a[_i][_j] != '1') continue;
                    network.addEdge(i * m + j + 1, _i * m + _j + 1, 1);
                }
            }
        }
    }
    // find max bipartite matching in this chessboard of 1's.

    int ans = network.calc(0, n*m + 1);
    cout << ans * q + (tot - 2*ans)*p << "\n";
}

int32_t main(){
    fast;
    int t = 1;
    // cin >> t;
    while(t--)
        solve();
    return 0;
}
