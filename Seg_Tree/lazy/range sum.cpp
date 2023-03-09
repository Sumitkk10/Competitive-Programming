#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL) 
#define ll long long
#define F first 
#define S second
using namespace std;
const int N = 1e6 + 5, MOD = 1e9 + 7;
long long n, q, a[N], seg[4*N], lazy[4*N];

void build(int vertex, int l, int r){
	lazy[vertex] = 0;
	if(r < l) return;
	if(l == r){
		seg[vertex] = a[l];
		return;
	}
	int mid = (l + r) / 2;
	build(2 * vertex, l, mid);
	build(2 * vertex + 1, mid + 1, r);
	seg[vertex] = seg[2 * vertex] + seg[2 * vertex + 1];
}

long long get(int vertex, int l, int r, int tl, int tr){
	if(lazy[vertex]){
		seg[vertex] += (r - l + 1) * lazy[vertex];
		if(l != r){
			lazy[2 * vertex] += lazy[vertex];
			lazy[2 * vertex + 1] += lazy[vertex];
		}
		lazy[vertex] = 0;
	}
	if(l > tr or r < tl) return 0;
	if(l >= tl and r <= tr)
		return seg[vertex];
	int mid = (l + r) / 2;
	long long ans = get(2 * vertex, l, mid, tl, tr);
	ans += get(2 * vertex + 1, mid + 1, r, tl, tr);
	return ans;
}

void upd(int vertex, int l, int r, int tl, int tr, int val){
	if(lazy[vertex]){
		seg[vertex] += (r - l + 1) * lazy[vertex];
		if(l != r){
			lazy[2 * vertex] += lazy[vertex];
			lazy[2 * vertex + 1] += lazy[vertex];
		}
		lazy[vertex] = 0;
	}
	if(l > tr or r < tl) return;
	if(l >= tl and r <= tr){
		seg[vertex] += (r - l + 1) * val;
		if(l != r){
			lazy[2 * vertex] += val;
			lazy[2 * vertex + 1] += val;
		}
		return;
	}
	int mid = (l + r) / 2;
	upd(2 * vertex, l, mid, tl, tr, val);
	upd(2 * vertex + 1, mid + 1, r, tl, tr, val);
	seg[vertex] = seg[2 * vertex] + seg[2 * vertex + 1];
}

void solve(){
	cin >> n >> q;
	for(int i = 1; i <= n; ++i)
		cin >> a[i];
	build(1, 1, n);
	while(q--){
		int type;
		cin >> type;
		if(type == 1){
			int l, r, v;
			cin >> l >> r >> v;
			upd(1, 1, n, l, r, v);
		}
		else{
			int l;
			cin >> l;
			cout << get(1, 1, n, l, l) << '\n';
		}
	}
}

int main() {
    fast;
    int t = 1;
    // cin >> t;
    while(t--)
    	solve();
	return 0;
}
