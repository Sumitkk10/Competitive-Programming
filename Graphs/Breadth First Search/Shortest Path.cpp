#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const int N = 1e6 + 5;
const int MOD = 1e9 + 7;
vector<ll> graph[N];
bool vis[N];
ll n, e, distanc[N];
queue<ll> q;

void bfs(ll source){
	vis[source] = true;
	q.push(source);
	distanc[source] = 0;
	while(!q.empty()){
		int node = q.front();
		q.pop();
		for(auto edge : graph[node]){
			if(!vis[edge]){
				distanc[edge] = distanc[node] + 1;
				q.push(edge);
				vis[edge] = true;
			}
		}
	}
}

int main(){
	fast;
	cin >> n >> e;
	for(int i = 0; i < e; ++i){
		int u, v; cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	ll qq; cin >> qq;
	memset(distanc, -1, sizeof(distanc));
	while(qq--){
		ll soure, dis, ans = 0;
		cin >> soure >> dis;
		bfs(soure);		
		for(int i = 0; i <= n; ++i) 
			if(distanc[i] == dis) 
				++ans;
		cout << ans << "\n";
		for(int i = 0; i <= n; ++i) distanc[i] = -1, vis[i] = 0;
        while(!q.empty()) 
        	q.pop();
	}
	return 0;
}
