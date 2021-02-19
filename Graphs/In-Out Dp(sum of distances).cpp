// find the distance of every node to a node


#include<bits/stdc++.h>
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;
const int MOD = 1e9 + 7;
const int N = 1e6 + 5;
vector<int> graph[N];
long long int in[N], out[N], subtree_size[N];

void yet_another_dfs(int source, int p){
    subtree_size[source] = 0;
    for(auto k : graph[source]) {
        if (k != p) {
            yet_another_dfs(k, source);
            subtree_size[source] += 1 + subtree_size[k];
        }
    }
}

void dfs(int source, int p){
    in[source] = 0;
    in[source] += subtree_size[source];
    for(auto k : graph[source]){
        if(k != p){
            dfs(k, source);
            in[source] += in[k];
        }
    }
}

void dfs1(int source, int p) {
    long long sum = 0;
    // going to siblings
    for(auto k : graph[source]){
        if(k != p){
            // these are the siblings;
            sum += ((subtree_size[k] + 1) * 2) + in[k];
        }
    }
    for(auto k : graph[source]){
        if(k != p){
            long long cur = sum - in[k] - ((subtree_size[k] + 1) * 2);
            out[k] = cur + out[source] + (subtree_size[1] + 1 - subtree_size[source]);
            dfs1(k, source);
        }
    }
}

void solve(){
    int n;
    cin >> n;
    for(int i = 1; i <= n - 1; ++i) {
        long long int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    // subtree_size[i] --> no of nodes in subtree excluding ith node;
    yet_another_dfs(1, 0);
    // in[i] --> total sum of subtree of i.
    dfs(1, 0);
    // out[i] --> how to calculate out[i] ??
    dfs1(1, 0);
    for(long long int i = 1; i <= n; ++i)
        cout << in[i] + out[i] <<  ' ';
}

int main() {
    fast;
    int t = 1;
    // cin >> t;
    while(t--)
        solve();
    return 0;
}
