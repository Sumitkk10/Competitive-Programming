#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define S second
#define F first 
#define pb push_back
using namespace std;
const int N = 1e6 + 5;
const int MOD = 1e9 + 7;
long long a[N], pre[N];
int par[100005][205], n, k;
vector<long long> dp(N), cur_dp(N);
 
long long C(int i, int j){
	return (pre[i] - pre[j]) * pre[j];
}
 
void compute(int l, int r, int tl, int tr, int kk){
	if(l > r)
		return;
	int mid = (l + r) / 2;
	pair<long long, int> p = {INT_MIN, mid};
	for(int i = tl; i < min(mid, tr + 1); ++i){
		if((dp[i] + C(mid, i)) > p.F){
			p.F = dp[i] + C(mid, i);
			p.S = i;
		}
	}
	par[mid][kk] = p.S;
	cur_dp[mid] = p.F;
	compute(l, mid - 1, tl, p.S, kk);
	compute(mid + 1, r, p.S, tr, kk);
}
 
void solve(){
	cin >> n >> k;
	for(int i = n - 1; i >= 0; --i)
		cin >> a[i];
	pre[0] = a[0];
	for(int i = 1; i < n; ++i)
	    pre[i] = pre[i - 1] + a[i];
	for(int i = 1; i <= k; ++i){
		compute(0, n - 1, 0, n - 1, i);
		dp = cur_dp;
	}
	cout << dp[n - 1] << '\n';
	int pos = n - 1, ct = k;
	while(ct > 0){
		cout << n - par[pos][ct] - 1 << ' ';
		pos = par[pos][ct];
		--ct;
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
