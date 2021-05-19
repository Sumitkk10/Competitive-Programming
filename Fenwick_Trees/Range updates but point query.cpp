// we just take the idea of difference array. Whole code is same, it's just that we do two updates here : 
// upd(l, val)
// upd(r + 1, -val)

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const int MOD = 1e9 + 7;
const int N = 1e6 + 5;
long long int n, fenwick[N];

void upd(int node, int val){
	for(int i = node; i <= n; i += (i & -i))
		fenwick[i] += val;
}

int query(int node){
	long long int sum = 0;
	for(int i = node; i >= 1; i -= (i & -i))
		sum += fenwick[i];
	return sum;
}

void solve(){
  memset(fenwick, 0, sizeof fenwick);
	int u;
	cin >> n >> u;
	while(u--){
		int l, r, val;
		cin >> l >> r >> val;
		++l, ++r;
		if(val == 0) continue;
		upd(l, val);
		upd(r + 1, -val);
	}
	int q;
	cin >> q;
	while(q--){
		int pos;
		cin >> pos;
		++pos;
		cout << query(pos) << '\n';
	}
}

int main() {
	fast;
	int t = 1;
    cin >> t;
	while(t--)
		solve();
}
