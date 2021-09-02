/*
in directed graphs, for finding cycles we need coloring.
but for undirected graphs, we can just use vis array.
if you need to find all cycles(or SCC) use kosaraju's algo.
*/

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const int N = 1e6 + 5;
const int MOD = 1e9 + 7;
int n, m, par[N], str, finish, col[N];
vector<int> graph[N];
bool ok;

void dfs(int node){
    col[node] = 1;
    for(auto k : graph[node]){
        if(col[k] == 0){
            par[k] = node;
            dfs(k);
        }
        else if(col[k] == 1){
            str = k;
            finish = node;
            ok = 1;
        }
    }
    col[node] = 2;
}

void solve(){
    cin >> n >> m;
    for(int i = 1; i <= m; ++i){
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }
    for(int i = 1; i <= n; ++i){
        if(col[i]) continue;
        dfs(i);
        if(ok){
            vector<int> ans;
            ans.push_back(str);
            while(finish != str){
                ans.push_back(finish);
                finish = par[finish];
            }
            ans.push_back(finish);
            reverse(ans.begin(), ans.end());
            cout << ans.size() << '\n';
            for(auto k : ans) cout << k << ' ';
            return;
        }
    }
    cout << "IMPOSSIBLE\n";
}

int main(){
    fast;
    int t = 1;
    // cin >> t;
    while(t--)
        solve();
    return 0;
}
