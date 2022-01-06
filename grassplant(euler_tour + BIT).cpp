#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define F first
#define S second
using namespace std;
const int N = 1e5 + 5;
const int MOD = 1e9 + 7;
vector<int> graph[N];
int fenwick[N], timer, dp[N][(int) log2(100005) + 2], n, q, lvl[N], tin[N], tout[N];

void upd(int node, int val){
	for(int i = node; i <= n; i += (-i & i))
		fenwick[i] += val;
}

int get(int node){
     int ans = 0;
     for(int i = node; i >= 1; i -= (i & -i))
          ans += fenwick[i];
     return ans;
}

void dfs(int source, int par, int level){
	dp[source][0] = par;
	lvl[source] = level;
	tin[source] = ++timer;
	for(auto k : graph[source])
		if(k != par)
			dfs(k, source, level + 1);
	tout[source] = timer;
}

void init(){
	dfs(1, -1, 0);
	for(int i = 1; i <= (log2(n)); ++i)
		for(int j = 1; j <= n; ++j)
			if(dp[j][i - 1] != -1)
				dp[j][i] = dp[dp[j][i - 1]][i - 1];
}

int LCA(int u, int v){
	if(lvl[u] > lvl[v]) swap(u, v);
	int d = lvl[v] - lvl[u];
	while(d){
		int jump = log2(d);
		v = dp[v][jump];
		d -= pow(2, jump);
	}
	if(v == u) 
		return v;
	for(int i = log2(n); i >= 0; --i){
		if(dp[v][i] != -1 && dp[v][i] != dp[u][i]){
			u = dp[u][i];
			v = dp[v][i];
		}
	}
	return dp[v][0];
}


void solve(){
	cin >> n >> q;
	for(int i = 0; i < n - 1; ++i){
		int u, v;
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	memset(dp, -1, sizeof dp);
	init();
	/*
	for(int i = 1; i <= n; ++i){
	     cout << i << ' ' << tin[i] << ' ' << tout[i] << endl;
	}
	*/
	while(q--){
		char type;
		cin >> type;
		if(type == 'P'){
			// update query
			// update root --> a with +1 and root --> b with +1 and root --> lca(a, b) with -2
			int u, v;
			cin >> u >> v;
			upd(tin[u], 1);
			upd(tin[v], 1);
			int p = LCA(u, v);
			// cout << u << ' ' << v << ' ' << p << endl;
			upd(tin[p], -2);
		}
		else{
			int u, v;
			cin >> u >> v;
			if(lvl[u] > lvl[v])
				swap(u, v);
			int ans = get(tout[v]) - get(tin[v] - 1);
			cout << ans << '\n';
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
