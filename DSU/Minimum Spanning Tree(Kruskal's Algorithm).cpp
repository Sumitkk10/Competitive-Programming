// MSP

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const int N = 1e6 + 5;
const int MOD = 1e9 + 7;
vector<pair<long long int, pair<long long int, long long int> > > edges;
long long int n, m, component[N], ans;

long long int find(long long int a){
	while(1){
		if(a == component[a]) return a;
		else{
			component[a] = component[component[a]];
			a = component[a];
		}
	}
}

void merge(long long int u, long long int v){
	long long int a = find(u), b = find(v);
	if(a != b)
		component[a] = component[b];
}

long long int MST(){
	int edge = 0;
	for(auto e : edges){
		if(edge == n - 1) break;
		long long int u = e.second.first;
		long long int v = e.second.second;
		long long int cost = e.first;
		if(component[u] != component[v]){
			++edge;
			ans += cost;
			merge(u, v);
		}
	}
	return ans;
}

int main(){
	fast;
	cin >> n >> m;
	for(int i = 1; i <= m; ++i){
		long long int u, v, c;
		cin >> u >> v >> c;
		edges.push_back({c, {u, v}});
	}
	for(int i = 0; i <= n; ++i) 
		component[i] = i;
	cout << MST();
	return 0;
}
