#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const int N = 1e6 + 5;
const int MOD = 1e9 + 7;
int n, q, a[N];

struct node{
    long long ans, pre, suf;
}seg_tree[4*N];

void build(int vertex, int l, int r){
    if(l > r)
        return;
    if(l == r){
        seg_tree[vertex].ans = 1;
        seg_tree[vertex].pre = 1;
        seg_tree[vertex].suf = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(2 * vertex, l, mid);
    build(2 * vertex + 1, mid + 1, r);
    long long cur = 0;
    if(a[mid] <= a[mid + 1]){
        cur += seg_tree[2 * vertex].pre * seg_tree[2*vertex + 1].suf;
        if(seg_tree[2 * vertex + 1].pre == (r - mid))
            seg_tree[vertex].pre += seg_tree[2 * vertex].pre;
        if(seg_tree[2 * vertex].suf == mid - l + 1)
            seg_tree[vertex].suf += seg_tree[2 * vertex + 1].suf;
    }
    cur += seg_tree[2 * vertex].ans + seg_tree[2 * vertex + 1].ans;
    seg_tree[vertex].ans = cur;
    seg_tree[vertex].pre += seg_tree[2 * vertex + 1].pre;
    seg_tree[vertex].suf += seg_tree[2 * vertex].suf;
}

long long get(int vertex, int l, int r, int tl, int tr){
    if(l > tr or r < tl) 
        return 0;
    if(l >= tl and r <= tr)
        return seg_tree[vertex].ans;
    int mid = (l + r) >> 1;
    long long cur = get(2 * vertex, l, mid, tl, tr);
    long long cur1 = get(2 * vertex + 1, mid + 1, r, tl, tr);
    if(a[mid] <= a[mid + 1]){
        if(mid >= tl and mid + 1 <= tr){
            long long cur_l = min((long long) mid - tl + 1, seg_tree[2 * vertex].pre);
            long long cur_r = min((long long) tr - mid, seg_tree[2 * vertex + 1].suf);
            // cout << l << ' ' << r << ' ' << cur_l << '\n';
            cur += (cur_l * cur_r);
        }
    }
    return (cur + cur1);
}

void update(int vertex, int l, int r, int point, int val){
    if(l > point or r < point) return;
    if(l == r){
        seg_tree[vertex].ans = 1;
        seg_tree[vertex].pre = 1;
        seg_tree[vertex].suf = 1;
        return;
    }
    int mid = (l + r) >> 1;
    if(point <= mid)
        update(2 * vertex, l, mid, point, val);
    else
        update(2 * vertex + 1, mid + 1, r, point, val);
    long long cur = 0;
    seg_tree[vertex].ans = 0;
    seg_tree[vertex].pre = 0;
    seg_tree[vertex].suf = 0;
    if(a[mid] <= a[mid + 1]){
        cur += seg_tree[2 * vertex].pre * seg_tree[2*vertex + 1].suf;
        if(seg_tree[2 * vertex + 1].pre == (r - mid))
            seg_tree[vertex].pre += seg_tree[2 * vertex].pre;
        if(seg_tree[2 * vertex].suf == mid - l + 1)
            seg_tree[vertex].suf += seg_tree[2 * vertex + 1].suf;
    }
    cur += seg_tree[2 * vertex].ans + seg_tree[2 * vertex + 1].ans;
    seg_tree[vertex].ans = cur;
    seg_tree[vertex].pre += seg_tree[2 * vertex + 1].pre;
    seg_tree[vertex].suf += seg_tree[2 * vertex].suf;
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
            int pos, val;
            cin >> pos >> val;
            a[pos] = val;
            update(1, 1, n, pos, val);
        }
        else{
            int l, r;
            cin >> l >> r;
            cout << get(1, 1, n, l, r) << '\n';
        }
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
