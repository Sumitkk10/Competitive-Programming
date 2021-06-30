#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const int MOD = 1e9 + 7;
const int N = 1e6 + 5;
long long int n, q, a[N], seg_tree[N][4];

void build(int vertex, int l, int r){
	if(l > r) return;
	if(l == r){
		// 1 --> max sub sum, 2--> max pre sum, 3 --> max suf sum, 4 --> sum
		seg_tree[vertex][1] = max(0LL, a[l]);
		seg_tree[vertex][2] = max(0LL, a[l]);
		seg_tree[vertex][3] = max(0LL, a[l]);
		seg_tree[vertex][4] = a[l];
		return;
	}
	int mid = (l + r) / 2;
	build(2 * vertex, l, mid);
	build(2 * vertex + 1, mid + 1, r); 
	seg_tree[vertex][1] = max({seg_tree[2*vertex][1], seg_tree[2 * vertex + 1][1], seg_tree[2 * vertex][3] + seg_tree[2 * vertex + 1][2]});
	seg_tree[vertex][2] = max({seg_tree[2 * vertex][2], seg_tree[2 * vertex][4] + seg_tree[2 * vertex + 1][2]});
	seg_tree[vertex][3] = max({seg_tree[2 * vertex + 1][3], seg_tree[2 * vertex + 1][4]  + seg_tree[2 * vertex][3]});
	seg_tree[vertex][4] = seg_tree[2 * vertex][4] + seg_tree[2 * vertex + 1][4];
}

void upd(int vertex, int l, int r, int pos, long long int val){
	if(l > pos or r < pos) return;
	if(l == r){
		seg_tree[vertex][1] = max(0LL, val);
		seg_tree[vertex][2] = max(0LL, val);
		seg_tree[vertex][3] = max(0LL, val);
		seg_tree[vertex][4] = val;
		return;
	}
	int mid = (l + r) / 2;
	upd(2 * vertex, l, mid, pos, val);
	upd(2 * vertex + 1, mid + 1, r, pos, val);
	seg_tree[vertex][1] = max({seg_tree[2*vertex][1], seg_tree[2 * vertex + 1][1], seg_tree[2 * vertex][3] + seg_tree[2 * vertex + 1][2]});
	seg_tree[vertex][2] = max({seg_tree[2 * vertex][2], seg_tree[2 * vertex][4] + seg_tree[2 * vertex + 1][2]});
	seg_tree[vertex][3] = max({seg_tree[2 * vertex + 1][3], seg_tree[2 * vertex + 1][4]  + seg_tree[2 * vertex][3]});
	seg_tree[vertex][4] = seg_tree[2 * vertex][4] + seg_tree[2 * vertex + 1][4];
}

long long answer(int vertex, int l, int r, int str, int endd){
	if(l > endd or r < str) return 0;
	if(l <= str and r >= endd)
		return seg_tree[vertex][1];
	int mid = (l + r) / 2;
	long long res = answer(2 * vertex, l, mid, str, endd);
	res = max(res, answer(2 * vertex + 1, mid + 1, r, str, endd));
	return res;
}

void solve(){
	cin >> n >> q;
	for(int i = 1; i <= n; ++i)
		cin >> a[i];
	build(1, 1, n);
	// cout << seg_tree[1][1] << '\n';
	while(q--){
		long long int k, val;
		cin >> k >> val;
		a[k] = val;
		upd(1, 1, n, k, val);
		cout << answer(1, 1, n, 1, n) << '\n';
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
