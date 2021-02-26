#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;
const int N = 500 + 5;
const int MOD = 1e9 + 7;
vector<pair<long long, pair<int, int> > > edges;
long long dis[N];
int n, m;

void bellman(int source){
    dis[source] = 0;
    for(int i = 0; i <= n - 1; ++i){
        for(auto k : edges){
            int u = k.second.first, v = k.second.second;
            long long x = k.first;
            dis[v] = min(dis[v], dis[u] + x);
        }
    }
}

int main() {
    fast;
    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
        dis[i] = LLONG_MAX;
    for(int i = 0; i < m; ++i){
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({w, {u, v}});
        edges.push_back({w, {v, u}});
    }
    bellman(1);
    int end;
    cin >> end;
    cout << dis[end] << "\n";
    return 0;
}
