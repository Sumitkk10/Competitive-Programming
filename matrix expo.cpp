#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const int N = 1e5 + 5;
const int MOD = 42373;
int n;

vector<vector<long long int> > multiply(vector<vector<long long int> >a, vector<vector<long long int> > b){
	vector<vector<long long> > ans(n, vector<long long int>(n, 0));
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			for(int tt = 0; tt < n; ++tt)
				ans[i][j] = (ans[i][j] + (a[i][tt]*b[tt][j])) % MOD;
		}
	}
	return ans;
}

vector<vector<long long int> > matrix_exponentiation(vector<vector<long long int> >a, int k){
	vector<vector<long long int> > res(n, vector<long long int> (n, 0));
	for(int i = 0; i < n; ++i)
		res[i][i] = 1;
	while(k > 0){
		if(k % 2)
			res = multiply(res, a);
		a = multiply(a, a);
		k /= 2;
	}
	return res;
}

void solve(){
	cin >> n;
	vector<vector<long long int> > a(n, vector<long long int> (n, 0));
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			cin >> a[i][j];
	int str, tar, k;
	cin >> str >> tar >> k;
	vector<vector<long long int> > ans = matrix_exponentiation(a, k);
	cout << ans[str - 1][tar - 1] % MOD << '\n';
}

int main(){
	fast;
	int t = 1;
	// cin >> t;
	while(t--)
		solve();
	return 0;
}
