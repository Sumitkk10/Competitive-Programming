// https://cses.fi/problemset/task/1137/

#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int n, q, tin[N], tout[N], tim;
long long val[N], seg_tree[4 * N];
vector<int> euler, graph[N];

void build(int vertex, int l, int r){
    if(r < l)
        return;
    if(l == r){
        seg_tree[vertex] = val[euler[l]];
        return;
    }
    int mid = (l + r) / 2;
    build(2 * vertex, l, mid);
    build(2 * vertex + 1, mid + 1, r);
    seg_tree[vertex] = seg_tree[2 * vertex] + seg_tree[2 * vertex + 1];
}

void update(int vertex, int l, int r, int node, int change, int node1){
    if(l > node or r < node)
        return;
    if(l == r){
        seg_tree[vertex] = seg_tree[vertex] - val[node1] + change;
        return;
    }
    int mid = (l + r) / 2;
    update(2 * vertex, l, mid, node, change, node1);
    update(2 * vertex + 1, mid + 1, r, node, change, node1);
    seg_tree[vertex] = seg_tree[2 * vertex] + seg_tree[2 * vertex + 1];
}

long long sum(int vertex, int l, int r, int str, int end){
    if(l > end or r < str)
        return 0;
    if(l >= str and r <= end)
        return seg_tree[vertex];
    int mid = (l + r) / 2;
    long long ans = sum(2 * vertex, l, mid, str, end);
    ans += sum(2 * vertex + 1, mid + 1, r, str, end);
    return ans;
}

void dfs(int source, int par){
    euler.push_back(source);
    tin[source] = tim;
    for(auto k : graph[source]) {
        if (k != par) {
            ++tim;
            dfs(k, source);
        }
    }
    tout[source] = tim;
}

int main() {
    cin >> n >> q;
    for(int i = 1; i <= n; ++i)
        cin >> val[i];
    for(int i = 1; i <= n - 1; ++i){
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs(1, -1);
    unordered_map<int, int> mp;
    for(int i = 0; i < euler.size(); ++i)
        mp[euler[i]] = i;
    build(1, 0, euler.size() - 1);
    while(q--){
        int x;
        cin >> x;
        if(x == 1){
            int node, change;
            cin >> node >> change;
            int pos = mp[node];
            update(1, 0, euler.size() - 1, pos, change, node);
            val[node] = change;
        }
        else{
            int node;
            cin >> node;
            int pos = mp[node];
            int diff = tout[node] - tin[node];
            cout << sum(1, 0, euler.size() - 1, pos, pos + diff) << "\n";
        }
    }
    return 0;
}
