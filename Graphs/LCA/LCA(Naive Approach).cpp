#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const int N = 1e6 + 5;
const int MOD = 1e9 + 7;
vector<ll> graph[N];
ll lvl[N], parent[N];
bool vis[N];

void dfs(int source, int level, int par){
	lvl[source] = level;
	vis[source] = true;
	parent[source] = par;
	for(auto k : graph[source])
		if(!vis[k])
			dfs(k, level + 1, source);
}

long long int LCA(int u, int v){
	if(lvl[u] > lvl[v]) swap(u, v);
	long long int d = lvl[v] - lvl[u];
	while(d--)
		v = parent[v];
	if(v == u) return u;
	while(parent[u] != parent[v]){
		u = parent[u]; 
		v = parent[v];
	}
	return parent[u];
}

int main(){
	fast;
	ll n;
	cin >> n;
	for(int i = 0; i < n - 1; ++i){
		long long int u, v;
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	dfs(1, 0, 1);
	long long int q;
	cin >> q;
	while(q--){
		long long int u, v;
		cin >> u >> v;
		cout << LCA(u, v) << "\n";
	}
	return 0;
}
