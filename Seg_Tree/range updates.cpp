#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const int MOD = 1e9 + 7;
vector<int> graph[1000005], euler;
int par[1000005], tin[1000005], tout[1000005], cur = 1;

void dfs(int node, int p){
    par[node] = p;
    euler.push_back(node);
    tin[node] = cur++;
    for(auto k : graph[node]){
        if(k == p) continue;
        dfs(k, node);
    }
    tout[node] = cur-1;
}

namespace ST {
    vector<ll> Black, lazy;

    void build(int n, int l, int r){
        if(l > r) return;
        Black[n] = r-l+1;
        if(l == r) return;

        int mid = (l+r)/2;
        build(2*n, l, mid);
        build(2*n+1, mid+1, r);
    }

    void init(int N){
        Black.resize(4*N);
        lazy.resize(4*N);
    
        build(1, 0, N-1);
    }

    void lazyUpdate(int n, int l, int r){
        if(lazy[n] == 0) return;
        Black[n] = (r-l+1)-Black[n];
    
        if(l < r){
            lazy[2*n] ^= 1;
            lazy[2*n+1] ^= 1;
        }
        lazy[n] = 0;
    }

    void flip(int n, int l, int r, int L, int R){
        lazyUpdate(n, l, r);
        if(r < L or R < l) return;
        if(L <= l and r <= R){
            lazy[n] ^= 1;
            lazyUpdate(n, l, r);
            return;
        }

        int mid = (l+r)/2;
        flip(2*n, l, mid, L, R);
        flip(2*n+1, mid+1, r, L, R);
        Black[n] = Black[2*n]+Black[2*n+1];
    }

    int query(int n, int l, int r, int L, int R){
        lazyUpdate(n, l, r);
        if(r < L or R < l) return 0;
        if(L <= l and r <= R) return Black[n];

        int mid = (l+r)/2;
        return query(2*n, l, mid, L, R)+
            query(2*n+1, mid+1, r, L, R);
    }
};

void solve(){
    int n;
    cin >> n;
    // everything is black intially.
    /*
    idea is for each type 1 query, i count the no. of black nodes in subtree of v and find no. of 
    black nodes without including subtree of v. then multiply those.
    */
    for(int i = 1; i <= n - 1; ++i){
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs(1, 0);
    // 0--> black;
    // 1 --> white;
    ST::init(n);
    ST::build(1, 1, n);
    int q;
    cin >> q;
    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int u, v;
            cin >> u >> v;
            if(par[u] == v) swap(u, v);
            long long ans = ST::query(1, 1, n, tin[v], tout[v]);
            long long ans1 = ST::query(1, 1, n, 1, n) - ans;
            cout << ans*ans1 << "\n";
        }
        else{
            int v;
            cin >> v;
            ST::flip(1, 1, n, tin[v], tout[v]);
        }
    }
}

int main(){
    fast;
    int t = 1;
    // cin >> t;
    while(t--)
        solve();
    return 0;
}
