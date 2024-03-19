#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define int long long
#define F first
#define S second
#define pb push_back
using namespace std;
using namespace __gnu_pbds; 
const int N = 1e6 + 5, MOD = 1e9 + 7;

#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update> 

struct Treap{ /// hash = 96814
    int len;
    const int ADD = 1000010;
    const int MAXVAL = 1000000010;
    unordered_map <long long, int> mp; /// Change to int if only int in treap
    tree<long long, null_type, less<long long>, rb_tree_tag, tree_order_statistics_node_update> T;

    Treap(){
        len = 0;
        T.clear(), mp.clear();
    }

    inline void clear(){
        len = 0;
        T.clear(), mp.clear();
    }

    inline void insert(long long x){
        len++, x += MAXVAL;
        int c = mp[x]++;
        T.insert((x * ADD) + c);
    }

    inline void erase(long long x){
        x += MAXVAL;
        int c = mp[x];
        if (c){
            c--, mp[x]--, len--;
            T.erase((x * ADD) + c);
        }
    }

    /// 1-based index, returns the K'th element in the treap, -1 if none exists
    inline long long kth(int k){
        if (k < 1 || k > len) return -1;
        auto it = T.find_by_order(--k);
        return ((*it) / ADD) - MAXVAL;
    }

    /// Count of value < x in treap
    inline int count(long long x){
        x += MAXVAL;
        int c = mp[--x];
        return (T.order_of_key((x * ADD) + c));
    }

    /// Number of elements in treap
    inline int size(){
        return len;
    }
};


void solve(){
	int n;
	cin >> n;
	int a[n + 1], v[n + 1], ans = 0;
	Treap s = Treap();
	for(int i = 1; i <= n; ++i){
		cin >> a[i];
		ans = max(ans, a[i]);
		s.insert(a[i]);
	}
	for(int i = 1; i <= n; ++i)
		cin >> v[i];
	int res = 1;
	for(int k = 2; k <= n; ++k){
		int rem = a[v[k - 1]];
		s.erase(rem);
		if(s.size() < k) break;
		int pos = s.size() - k + 1;
		if(k * (s.kth(pos)) > ans){
			ans = k * (s.kth(pos));
			res = k;
		}
	}
	cout << ans << ' ' << res << "\n";
}

int32_t main(){
	fast;
	int t = 1;
	cin >> t;
	while(t--)
		solve();
	return 0;
}
