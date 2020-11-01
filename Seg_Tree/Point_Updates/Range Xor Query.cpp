#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const int N = 1e6 + 5;
const int MOD = 1e9 + 7;
ll seg_tree[4*N], a[N];

void build(int vertex, int l, int r){
	if(l == r)
		seg_tree[vertex] = a[l];
	else{
		int mid = (l + r) / 2;
		build(2 * vertex, l, mid);
		build((2 * vertex) + 1, mid + 1, r);
		seg_tree[vertex] = ((seg_tree[2 * vertex]) ^ (seg_tree[(2 * vertex) + 1]));
	}
}

ll xor_sum_query(int vertex, int l, int r, int x, int y){
	if(r < x || l > y || l > r) 
		return 0;
	if(x <= l && r <= y)
		return seg_tree[vertex];
	int mid = (l + r) / 2;
	long long int ans = xor_sum_query(2 * vertex, l, mid, x, y);
	long long int ans1 = xor_sum_query((2 * vertex) + 1, mid + 1, r, x, y);
	return (ans ^ ans1);
}

int main(){
	fast;	
	int n, q;
	cin >> n >> q;
	for(int i = 0; i < n; ++i)
		cin >> a[i];	
	memset(seg_tree, INT_MAX, sizeof(seg_tree));
	build(1, 0, n - 1);
	while(q--){
		int x, y;
		cin >> x >> y;
		--x, --y;
		cout << xor_sum_query(1, 0, n - 1, x, y) << '\n';
	}
	return 0;
}
