// Longest path in a DAG

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const int N = 1e6 + 5;
const int MOD = 1e9 + 7;
vector<int> graph[N];
queue<int> q;
int LPD[N], indegree[N];
bool vis[N];

void dfs(int source){
	vis[source] = 1;
	for(auto kk : graph[source]){
		indegree[kk]++;
		if(!vis[kk])
			dfs(kk);
	}
}

void topo(){
	while(!q.empty()){
		int x = q.front();
		q.pop();
		for(auto k : graph[x]){
			if(!vis[k]){
				indegree[k]--;
				if(indegree[k] == 0){
					q.push(k);
					vis[k] = true;
				}
				LPD[k] = max(LPD[k], LPD[x] + 1);
			}
		}
	}
}

int main(){
	fast;
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < m; ++i){
		int u, v;
		cin >> u >> v;
		graph[u].push_back(v);
	}
	for(int i = 1; i <= n; ++i)
		if(!vis[i])
			dfs(i);
	memset(vis, 0, sizeof(vis));
	for(int i = 1; i <= n; ++i){
		if(!indegree[i]){
			q.push(i);
			vis[i] = true;
		}
	}
	topo();
	int ans = 0;
	for(int i = 1; i <= n; ++i)
		ans = max(ans, LPD[i]);
	cout << ans << '\n';
	return 0;
}
