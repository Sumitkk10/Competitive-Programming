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
		seg_tree[vertex] = seg_tree[2*vertex] + seg_tree[(2*vertex) + 1];
	}
}

ll sum(int vertex, int l, int r, int x, int y){
	if(r < x || l > y) return 0;
	if(x <= l && r <= y)
		return seg_tree[vertex];
	int mid = (l + r) / 2;
	long long int ans = sum(2 * vertex, l, mid, x, y);
	long long int ans1 = sum((2 * vertex) + 1, mid + 1, r, x, y);
	return ans + ans1;
}

void update(int vertex, int l, int r, int idx, int x){
	if(r < idx || l > idx) return;
	if(l == r){
		seg_tree[vertex] += x; 
		return;
	}
	int mid = (l + r) / 2;
	update(2 * vertex, l, mid, idx, x);
	update((2 * vertex) + 1, mid + 1, r, idx, x);
	seg_tree[vertex] = seg_tree[2 * vertex] + seg_tree[(2 * vertex) + 1];
}

int main(){
	fast;	
	int n, q;
	cin >> n >> q;
	for(int i = 0; i < n; ++i)
		cin >> a[i];
	build(1, 0, n - 1);
	while(q--){
		int which_type;
		cin >> which_type;
		if(which_type == 2){ // return the sum;
			int l, r;
			cin >> l >> r;
			--l, --r;
			cout << sum(1, 0, n - 1, l, r) << '\n';
		}
		else{ // update the ith index;
			int i, x;
			cin >> i >> x;
			--i;
			int y = x;
			x = x - a[i];
			update(1, 0, n - 1, i, x);
			a[i] = y;
		}
	}
	return 0;
}
