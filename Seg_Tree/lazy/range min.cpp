#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const ll N = 1e6 + 5;
const ll MOD = 1e9 + 7;
ll n, a[N], q, lazy[4*N], val[4*N];

void build(ll vertex, ll l, ll r){
    lazy[vertex] = 0;
    if(l > r)
        return;
    if(l == r){
        val[vertex] = a[l];
        return;
    }
    ll mid = (l + r) / 2;
    build(2 * vertex, l, mid);
    build(2 * vertex + 1, mid + 1, r);
    val[vertex] = min(val[2 * vertex], val[2 * vertex + 1]);
}

void update(ll vertex, ll l, ll r, ll tl, ll tr, ll value){
    if(lazy[vertex] != 0){
        val[vertex] += lazy[vertex];
        lazy[2 * vertex] += lazy[vertex];
        lazy[2 * vertex + 1] += lazy[vertex];
        lazy[vertex] = 0;
    }
    if(l > tr or r < tl)
        return;
    if(l >= tl and r <= tr){
        val[vertex] += value;
        lazy[2 * vertex] += value;
        lazy[2 * vertex + 1] += value;
        return;
    }
    ll mid = (l + r) / 2;
    update(2 * vertex, l, mid, tl, tr, value);
    update(2 * vertex + 1, mid + 1, r, tl, tr, value);
    val[vertex] = min(val[2 * vertex], val[2 * vertex + 1]);
}

ll get(ll vertex, ll l, ll r, ll tl, ll tr){
    if(lazy[vertex] != 0){
        val[vertex] += lazy[vertex];
        lazy[2 * vertex] += lazy[vertex];
        lazy[2 * vertex + 1] += lazy[vertex];
        lazy[vertex] = 0;
    }
    if(l > tr or r < tl)
        return LLONG_MAX;
    if(l >= tl and r <= tr)
        return val[vertex];
    ll mid = (l + r) / 2;
    return min(get(2 * vertex, l, mid, tl, tr), get(2 * vertex + 1, mid + 1, r, tl, tr));
}

void solve(){
    cin >> n;
    for(ll i = 0; i < n; ++i)
        cin >> a[i];
    for(ll i = 0; i < 4*N; ++i)
        val[i] = LLONG_MAX;
    build(1, 0, n - 1);
    cin >> q;
    string s;
    getline(cin, s);
    while(q--){
        getline(cin, s);
        vector<ll> query;
        string a;
        for(ll i = 0; i < s.size(); ++i){
            if(s[i] == ' '){
                ll x = stoll(a);
                a.clear();
                query.push_back(x);
            }
            a.push_back(s[i]);
        }
        ll x = stoll(a);
        query.push_back(x);
        if(query.size() == 2){
            if(query[0] <= query[1])
                cout << get(1, 0, n - 1, min(query[0], query[1]), max(query[0], query[1])) << '\n';
            else
                cout << min(get(1, 0, n - 1, query[0], n - 1), get(1, 0, n - 1, 0, query[1])) << '\n';
        }
        else{
            if(query[0] <= query[1])
                update(1, 0, n - 1, min(query[0], query[1]), max(query[0], query[1]), query[2]);
            else{
                update(1, 0, n - 1, query[0], n - 1, query[2]);
                update(1, 0, n - 1, 0, query[1], query[2]);
            }
        }
    }
}

int main(){
    fast;
    ll t = 1;
    // cin >> t;
    while(t--)
        solve();
    return 0;
}
