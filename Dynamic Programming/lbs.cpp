// https://dunjudge.me/analysis/problems/917/

#include "bits/stdc++.h"
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long
using namespace std;
const int N = 1e6 + 5;
int seg_tree[4*N];

/*
for each index find lis ending at i and
find lds starting at i.
answer will be max of lis[i] + lds[i] over each index i.
*/

ll max_query(int vertex, int l, int r, int x, int y){
    if(r < x || l > y || l > r) 
        return 0;
    if(x <= l && r <= y)
        return seg_tree[vertex];
    int mid = (l + r) / 2;
    long long int ans = max_query(2 * vertex, l, mid, x, y);
    long long int ans1 = max_query((2 * vertex) + 1, mid + 1, r, x, y);
    return max(ans, ans1);
}

void update(int vertex, int l, int r, long long int idx, long long int x){
    if(r < idx || l > idx || l > r) return;
    if(l == r){
        seg_tree[vertex] = x;
        return;
    }
    int mid = (l + r) / 2;
    update(2 * vertex, l, mid, idx, x);
    update((2 * vertex) + 1, mid + 1, r, idx, x);
    seg_tree[vertex] = max(seg_tree[2 * vertex], seg_tree[(2 * vertex) + 1]);
}

void solve(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i)
        cin >> a[i];
    /*
    now the values can be upto 10^9 but observe that we don't really need values 
    so we can compress the values to uptil 10^6.
    */
    vector<pair<int, int> > comp;
    for(int i = 0; i < a.size(); ++i)
        comp.push_back({a[i], i});
    sort(comp.begin(), comp.end());
    int ct = 0;
    a[comp[0].second] = ct;
    for(int i = 1; i < comp.size(); ++i){
        if(comp[i].first != comp[i - 1].first)
            ++ct;
        a[comp[i].second] = ct;
    }
    /*
    for(int i = 0; i < n; ++i)
        cout << a[i] << " ";
    everything is compressed now
    */
    int lis[n], lds[n];
    lis[0] = 1;
    update(1, 0, n - 1, a[0], 1);
    for(int i = 1; i < n; ++i){
        if(a[i] == 0){
            lis[i] = 1;
            update(1, 0, n - 1, a[i], 1);
            continue;
        }
        lis[i] = max_query(1, 0, n - 1, 0, a[i] - 1) + 1;
        update(1, 0, n - 1, a[i], lis[i]);
    }
    /*
    for(int i = 0; i < n; ++i)
        cout << lis[i] << " ";
        lis is created.
    */
    reverse(a.begin(), a.end());
    memset(seg_tree, 0, sizeof seg_tree);
    lds[0] = 1;
    update(1, 0, n - 1, a[0], 1);
    for(int i = 1; i < n; ++i){
        if(a[i] == 0){
            lds[i] = 1;
            update(1, 0, n - 1, a[i], 1);
            continue;
        }
        lds[i] = max_query(1, 0, n - 1, 0, a[i] - 1) + 1;
        update(1, 0, n - 1, a[i], lds[i]);
    }
    reverse(a.begin(), a.end());
    int ans = 0;
    for(int i = 0; i < n; ++i)
        ans = max(ans, lis[i] + lds[n - i - 1] - 1);
    cout << ans << "\n";
}

int main(){
    fast;
    int t = 1;
    // cin >> t;
    while(t--)
        solve();
    return 0;
}
