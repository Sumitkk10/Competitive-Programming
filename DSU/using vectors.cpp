#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const int N = 1e6 + 5;
const int MOD = 1e9 + 7;
vector<ll> members[N];
ll component[N];

ll find(ll a){
	return component[a];
}
ll uni(ll a, ll b){
	if(members[a].size() > members[b].size())
		swap(a, b);
	for(int i = 0; i < members[a].size(); ++i){
		component[members[a][i]] = b;
		members[b].push_back(members[a][i]);
	}
}

int main(){
	fast;
	ll n, m;
	cin >> n >> m;
	for(int i = 1; i <= n; ++i){
		component[i] = i;
		members[i].push_back(i);
	}
	while(m--){
		ll q, u, v;
		cin >> q >> u >> v;
		if(q == 1){
			ll a = find(u), b = find(v);
			if(a == b) continue;
			uni(a, b);
		}
		else
			cout << (find(u) == find(v) ? "YES\n" : "NO\n");
	}
	return 0;
}
