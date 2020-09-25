// Each cell of the matrix can be either 0 or 1. If a cell is 0, that means it cannot be visited and if it is 1, then it can be visited. 
// Allowed moves are up, down, left and right. 
// Help Micro to find out if he can reach from the cell (1, 1) to the cell (N, M) , it is guaranteed that the cells (1,1) and (N, M) have value 1.

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const int N = 15;
const int MOD = 1e9 + 7;
ll n, a[N][N], m;
bool yo;

ll floodfill(int i, int j){
	if(a[i][j] == 0 || i < 0 || j < 0 || i >= n || j >= m) return 0;
	if(i == n - 1 && j == n - 1){ 
		yo = true;
		return 0;
	}
	if(i < n) floodfill(i + 1, j);
	if(j < m) floodfill(i , j + 1);
}

int main(){
	fast;
	cin >> n >> m;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j) 
            cin >> a[i][j];
	floodfill(0, 0);	
	if(yo) cout << "Yes\n";
	else cout << "No\n";
	return 0;
}
