// this is for school purposes
// lazy to calculate adjoint of 3x3 matrix

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const int N = 1e6 + 5;
const int MOD = 1e9 + 7;

void solve(){
    int n;
    cin >> n;
    int a[n + 1][n + 1];
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            cin >> a[i][j];
    if(n == 2){
        long long determinant = (a[1][1] * a[2][2]) - (a[1][2] * a[2][1]);
        cout << "determinant : " << determinant << endl;
        long long adjoint[n + 1][n + 1];
        adjoint[1][1] = a[n][n];
        adjoint[n][n] = a[1][1];
        adjoint[1][2] = -a[1][2];
        adjoint[2][1] = -a[2][1];
        cout << "adjoint : \n";
        for(int i = 1; i <= n; ++i){
            for(int j = 1; j <= n; ++j)
                cout << adjoint[i][j] << ' ';
            cout << endl;
        }
        cout << (determinant == 0 ? "No Inverse\n" : "Inverse exists\n");
        if(determinant != 0)
            cout << "For inverse, just multiply reciprocal of determinant with adjoint :) \n";
    }
    else{
        long long determinant = (a[1][1] * ((a[2][2] * a[3][3]) - (a[2][3] * a[3][2])));
        determinant += a[1][3] * ((a[2][1] * a[3][2]) - (a[2][2] * a[3][1]));
        determinant += (-a[1][2] * ((a[2][1] * a[3][3]) - (a[2][3] * a[3][1])));
        cout << "determinant : " << determinant << endl;
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
