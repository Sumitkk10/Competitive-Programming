#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const int N = 1e6 + 5;
const int MOD = 1e9 + 7;
ll a[N];
set<ll>* seg_tree;

void build(int vertex, int l, int r){
	if(l == r)
		seg_tree[vertex].insert(a[l]);
	else{
		int mid = (l + r) / 2;
		build(2 * vertex, l, mid);
		build((2 * vertex) + 1, mid + 1, r);
		seg_tree[vertex].insert(seg_tree[2 * vertex].begin(), seg_tree[2 * vertex].end());
		seg_tree[vertex].insert(seg_tree[(2 * vertex) + 1].begin(), seg_tree[(2 * vertex) + 1].end());
	}
}

set<ll> distinct_query(int vertex, int l, int r, int x, int y){
	set<ll> realans;
	if(r < x || l > y || l > r) 
		return realans;
	if(x <= l && r <= y)
		return seg_tree[vertex];
	int mid = (l + r) / 2;
	set<ll> ans = distinct_query(2 * vertex, l, mid, x, y);
	realans.insert(ans.begin(), ans.end());
	set<ll> ans1 = distinct_query((2 * vertex) + 1, mid + 1, r, x, y);
	realans.insert(ans1.begin(), ans1.end());
	return realans;
}

void init(ll n){
	ll h = (int) ceil(log2(n));
	h = (2 * pow(2, h)) - 1;
	seg_tree = new set<ll>[h];
}

int main(){
	fast;	
	int n;
	cin >> n;
	for(int i = 0; i < n; ++i)
		cin >> a[i];
	init(n);
	build(1, 0, n - 1);
	int q;
	cin >> q;
	while(q--){
		int x, y;
		cin >> x >> y;
		--x, --y;
		set<ll> ans = distinct_query(1, 0, n - 1, x, y);
		cout << ans.size() << '\n';
	}
	return 0;
}
