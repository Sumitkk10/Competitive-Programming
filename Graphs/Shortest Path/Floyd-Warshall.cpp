#include <bits/stdc++.h>
#define ll long long int    
#define ld long double
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;
const ll MOD = 1e9 + 7, N = 503, INF = 1e18;
ll n, m, q;
 
int main() {
    fast;
    cin >> n >> m >> q;
    ll dis[n+1][n+1];
    for(int i = 0; i <= n; ++i){
    	for(int j = 1; j <= n; ++j)
    		dis[i][j] = INF;
    	dis[i][i] = 0;
    }
    for(int i = 1; i <= m; ++i){
    	ll a, b, c;
        cin >> a >> b >> c;
        dis[a][b] = min(dis[a][b], c);
        dis[b][a] = min(dis[b][a], c);
    }
    for(int k = 1; k <= n; ++k){
    	for(int i = 1; i <= n; ++i){
    		for(int j = 1; j <= n; ++j){
    			dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    		}
    	}
    }
    for(int i = 0; i < q; ++i){
    	int a, b;
    	cin >> a >> b;
    	if(dis[a][b] == INF) cout << "-1\n";
    	else cout << dis[a][b] << "\n";
    }
    return 0;
}
