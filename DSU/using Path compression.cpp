// I prefer it this way.. 

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const int N = 1e6 + 5;
const int MOD = 1e9 + 7;
ll n, m;
ll parent[N];

ll find(int a){
	while(1){
		if(a == parent[a]) return a;
		else{
			parent[a] = parent[parent[a]];
			a = parent[a];
		}
	}
}

void merge(int u, int v){
	int a = find(u), b = find(v);
	if(a == b) return;
	parent[a] = b;
}

int main(){
	fast;
	cin >> n >> m;
	for(int i = 1; i <= n; ++i)
		parent[i] = i;
	while(m--){
		string s;
		cin >> s;
		if(s == "union"){
			int u, v;
			cin >> u >> v;
			merge(u, v);
		}
		else{
			int u, v;
			cin >> u >> v;
			cout << (find(u) == find(v) ? "YES\n" : "NO\n");
		}
	}
	return 0;
}
