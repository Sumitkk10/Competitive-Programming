// first create the next_occurence array and now just count the no of number from l to r whose next_occurencce is > r.

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
using namespace std;
const int N = 1e6 + 5;
const int MOD = 1e9 + 7;
int n, a[N], next_occur[N];
vector<int> seg_tree[4 * N];

vector<int> merge(vector<int> l, vector<int> r){
    vector<int> ans;
    int i = 0, j = 0;
    while(i < l.size() and j < r.size()){
        if(l[i] <= r[j]) {
            ans.push_back(l[i]);
            ++i;
        }
        else{
            ans.push_back(r[j]);
            ++j;
        }
    }
    while(i < l.size()){
        ans.push_back(l[i]);
        ++i;
    }
    while(j < r.size()){
        ans.push_back(r[j]);
        ++j;
    }
    return ans;
}

void build(int vertex, int l, int r){
    if(r < l)
        return;
    if(l == r) {
        seg_tree[vertex].push_back(next_occur[l]);
        return;
    }
    int mid = (l + r) / 2;
    build(2 * vertex, l, mid);
    build(2 * vertex + 1, mid + 1, r);
    seg_tree[vertex] = merge(seg_tree[2 * vertex], seg_tree[2 * vertex + 1]);
}

long long int find(int vertex, int l, int r, int str, int end, int search){
    if(l > end or r < str)
        return 0;
    if(l >= str and r <= end){
        int low = 0, high = seg_tree[vertex].size(), ok = -1;
        while(low <= high){
            int mid = (low + high) / 2;
            if(seg_tree[vertex][mid] > search){
                ok = mid;
                high = mid - 1;
            }
            else
                low = mid + 1;
        }
        if(ok == -1)
            return 0;
        return seg_tree[vertex].size() - ok;
    }
    int mid = (l + r) / 2;
    long long int ans = find(2 * vertex, l, mid, str, end, search);
    ans += find(2 * vertex + 1, mid + 1, r, str, end, search);
    return ans;
}

int main() {
    fast;
    cin >> n;
    for(int i = 0; i < n; ++i)
        cin >> a[i];
    map<int, int> mp;
    for(int i = 0; i < n; ++i){
        if(mp[a[i]])
            next_occur[mp[a[i]]] = i + 1;
        mp[a[i]] = i + 1;
    }
    for(int i = 1; i <= n; ++i) {
        if (!next_occur[i])
            next_occur[i] = n + 1;
        // cout << next_occur[i] << ' ';
    }
    // cout << endl;
    build(1, 1, n);
    int q;
    cin >> q;
    while(q--){
        int l, r;
        cin >> l >> r;
        cout << find(1, 1, n, l, r, r) << '\n';
    }
    return 0;
}
