// This code of HLD has bugs. 
// but your idea should be clear.

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const int N = 1e6 + 5;
const int MOD = 1e9 + 7;
vector<int> graph[N], cost[N], idx[N], edge(N);
int n, dp[N][(long long) log2(N)], dpt[N], subtree[N];
int chain_head[N], arr[N], pos[N], chainNo, which_chain[N], cur_idx;
int seg_tree[4 * N];

void build(int vertex, int l, int r){
	if(l == r){
		seg_tree[vertex] = arr[l];
		return;
	}
	int mid = (l + r) / 2;
	build(2 * vertex, l, mid);
	build(2 * vertex + 1, mid + 1, r);
	seg_tree[vertex] = seg_tree[2 * vertex] + seg_tree[2 * vertex + 1];
}

int sum(int vertex, int l, int r, int x, int y){
	if(l > y or r < x)
		return 0;
	if(l >= x and r <= y)
		return seg_tree[vertex];
	int mid = (l + r) / 2;
	return (sum(2 * vertex, l, mid, x, y) + sum(2 * vertex + 1, mid + 1, r, x, y));
}

void update(int vertex, int l, int r, int idx, int x){
	if(r < idx || l > idx) return;
	if(l == r){
		seg_tree[vertex] = x; 
		return;
	}
	int mid = (l + r) / 2;
	update(2 * vertex, l, mid, idx, x);
	update((2 * vertex) + 1, mid + 1, r, idx, x);
	seg_tree[vertex] = seg_tree[2 * vertex] + seg_tree[(2 * vertex) + 1];
}

void HLD(int node, int costs, int par){
	if(chain_head[chainNo] == -1)
		chain_head[chainNo] = node;
	
	which_chain[node] = chainNo;
	pos[node] = cur_idx;
	arr[cur_idx] = costs;
	++cur_idx;
	int mx = -1, id, ncost;
	
	for(int j = 0; j < graph[node].size(); ++j){
		if(subtree[graph[node][j]] > mx and graph[node][j] != par){
			ncost = cost[node][j];
			mx = subtree[graph[node][j]];
			id = graph[node][j];
		}
	}
	
	if(mx != -1)
		HLD(id, ncost, node);
	
	for(int j = 0; j < graph[node].size(); ++j){
		if(graph[node][j] != par and graph[node][j] != id){
			chainNo++;
			HLD(graph[node][j], cost[node][j], node);
		}
	}
}

int query_up(int u, int v){
	if(u == v)
		return 0;
	int uchain, vchain = which_chain[v], ans = -1;
	while(true){
		uchain = which_chain[u];
		if(uchain == vchain){
			if(u == v)
				break;
			ans += sum(1, 1, N, pos[v], pos[u]);
			break;
		}
		ans += sum(1, 1, N, pos[chain_head[uchain]], pos[u]);
		u = chain_head[uchain];
		u = dp[u][0];
	}
	return ans;
}

ll LCA(int u, int v){
	if(dpt[u] > dpt[v]) swap(u, v);
	ll d = dpt[v] - dpt[u];
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

void dfs(int node, int parent, int lvl){
	dp[node][0] = parent;
	dpt[node] = lvl;
	subtree[node] = 1;
	
	for(int i = 0; i < graph[node].size(); ++i){
		if(graph[node][i] != parent){
			edge[idx[node][i]] = graph[node][i];
			dfs(graph[node][i], node, lvl + 1);
			subtree[node] += subtree[graph[node][i]];
		}
	}
}

void init(){
	dfs(1, 0, 0);
	
	for(int i = 1; i <= log2(n); ++i){
		for(int j = 1; j <= n; ++j){
			if(dp[j][i - 1] != -1)
				dp[j][i] = dp[dp[j][i - 1]][i - 1];
		}
	}
	
	HLD(1, -1, -1);
}

void solve(){
	cin >> n;
	
	for(int i = 1; i < n; ++i){
		int u, v, c;
		cin >> u >> v >> c;
		graph[u].push_back(v);
		cost[u].push_back(c);
		idx[u].push_back(i);

		graph[v].push_back(u);
		cost[v].push_back(c);
		idx[v].push_back(i);
	}

	memset(dp, -1, sizeof dp);
	
	memset(chain_head, -1, sizeof chain_head);
	
	init();
	
	build(1, 1, N);

	int q;
	cin >> q;

	while(q--){
		int x;
		cin >> x;
		if(x == 1){
			int ed, val;
			cin >> ed >> val;
			update(1, 1, N, pos[edge[ed]], val);
		}
		else{
			int u, v;
			cin >> u >> v;
			int p = LCA(u, v);
			int ans = query_up(u, p);
			ans += query_up(v, p);
			cout << ans << "\n";
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
