#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const int N = 1e6 + 5;
const int MOD = 1e9 + 7;
vector<ll> graph[N];
bool vis[N];
ll height[N], dp[N][(ll) log2(N)], n;
string s;

void dfs(int source, int par, int dept){
	height[source] = dept;
	dp[source][0] = par;
	vis[source] = 1;
	for(auto k : graph[source])
		if(!vis[k])
			dfs(k, source, dept + 1); 
}

void binary(int x){
	while(x > 0){
		s.push_back((x % 2) + '0');
		x /= 2;
	}
	reverse(s.begin(), s.end());
}

ll find_kth_par(int u, int k){
	for(int i = 0; i < s.size(); ++i)
		if(s[i] == '1')
			u = dp[u][s.size() - i - 1];
	return u;
}

void init(){
	for(int i = 1; i <= log2(n); ++i)
		for(int j = 0; j < n; ++j)
			if(dp[j][i - 1] != -1)
				dp[j][i] = dp[dp[j][i - 1]][i - 1];
}

int main(){
	fast;
	cin >> n;
	for(int i = 1; i <= n - 1; ++i){
		int u, v;
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	dfs(0, -1, 0);
	init();
	ll q;
	cin >> q;
	while(q--){
		int x, k;
		cin >> x >> k;
		if(k > height[x]) cout << "-1\n";
		else{
			binary(k);
			// cout << s << " "; 
			cout << find_kth_par(x, k) << "\n";
			while(s.size())
				s.pop_back();
		}
	}
	return 0;
}
