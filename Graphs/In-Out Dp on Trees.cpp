#include<bits/stdc++.h>
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;
const int MOD = 1e9 + 7;
const int N = 1e6 + 5;
vector<int> graph[N];
int in[N], out[N];

void dfs(int source, int p){
    in[source] = 0;
    for(auto k : graph[source]){
        if(k != p){
            dfs(k, source);
            in[source] = max(in[source], 1 + in[k]);
        }
    }
}

void dfs1(int source, int p) {
    int mx = -2, mx1 = -2;
    for(auto k : graph[source]){
        if(k != p){
            if(in[k] > mx){
                mx1 = mx;
                mx = in[k];
            }
            else if(in[k] > mx1)
                mx1 = in[k];
        }
    }
    for(auto k : graph[source]){
        if(k != p){
            int cur = mx;
            if(cur == in[k])
                cur = mx1;
            out[k] = max(out[source] + 1, 2 + cur);
            dfs1(k, source);
        }
    }
}

void solve(){
    int n;
    cin >> n;
    for(int i = 1; i <= n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs(1, 0);
    dfs1(1, 0);
    for(int i = 1; i <= n; ++i)
        cout << max(in[i], out[i]) <<  ' ';
}

int main() {
    fast;
    int t = 1;
    // cin >> t;
    while(t--)
        solve();
    return 0;
}
