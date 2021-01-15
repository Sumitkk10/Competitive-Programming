// q queries to find the kth largest in the range l..r


#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const int N = 100000 + 5;
const int MOD = 1e9 + 7;
int n, q, a[N];
vector<int> merge_sort_tree[4 * N];

vector<int> merge(vector<int> l, vector<int> r){
    vector<int> ans;
    int i = 0, j = 0;
    if(l.size() > r.size())
        swap(l, r);
    // l is shorter.
    while(i < l.size() and j < r.size()){
        if(l[i] <= r[j]){
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
    if(l == r) {
        merge_sort_tree[vertex].push_back(a[l]);
        return ;
    }
    int mid = (l + r) / 2;
    build(2 * vertex, l, mid);
    build((2 * vertex) + 1, mid + 1, r);
    merge_sort_tree[vertex] = merge(merge_sort_tree[2 * vertex], merge_sort_tree[(2 * vertex) + 1]);
}

int find(int vertex, int str, int end, int l, int r, int search){
    if(str > r || end < l)
        return 0;
    if(str >= l && end <= r){
        return upper_bound(merge_sort_tree[vertex].begin(), merge_sort_tree[vertex].end(), search) - merge_sort_tree[vertex].begin();
    }
    int mid = (str + end) / 2;
    return (find(2 * vertex, str, mid, l, r, search) + find((2 * vertex) + 1, mid + 1, end, l, r, search));
}

int main() {
    fast;
    cin >> n >> q;
    for(int i = 0; i < n; ++i)
        cin >> a[i];
    build(1, 0, n - 1);
    while(q--){
        int l, r, k;
        cin >> l >> r >> k;
        --l, --r;
        k = (r - l + 2) - k;
        int low = 0, high = 1e9, ok;
        while(low <= high){
            int mid = (low + high) / 2;
            int ans = find(1, 0, n - 1, l, r, mid);
            if(ans >= k){
                ok = mid;
                high = mid - 1;
            }
            else
                low = mid + 1;
        }
        cout << ok << '\n';
    }
    return 0;
}
