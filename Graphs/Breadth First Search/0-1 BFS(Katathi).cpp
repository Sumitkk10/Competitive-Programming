#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const int N = 1003;
const int MOD = 1e9 + 7;
int n, m, dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
char a[N][N];

long long bfs(){
    deque<pair<int, int> > q;
    int dis[n + 1][m + 1];
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
            dis[i][j] = INT_MAX;
    dis[1][1] = 0;
    q.push_back({1, 1});
    while(!q.empty()){
        int i = q.front().first, j = q.front().second;
        q.pop_front();
        for(int qq = 0; qq < 4; ++qq){
            int cur_i = i + dx[qq], cur_j = j + dy[qq];
            if(cur_i < 1 or cur_j < 1 or cur_i > n or cur_j > m) continue;
            if(a[cur_i][cur_j] == a[i][j]){
                if(dis[cur_i][cur_j] > dis[i][j]){
                    dis[cur_i][cur_j] = dis[i][j];
                    q.push_front({cur_i, cur_j});
                }
            }
            else{
                if(dis[cur_i][cur_j] > dis[i][j] + 1){
                    dis[cur_i][cur_j] = dis[i][j] + 1;
                    q.push_back({cur_i, cur_j});
                }
            }
        }
    }
    return dis[n][m];
}

void solve(){
    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
            cin >> a[i][j];
    cout << bfs() << '\n';
}

int main(){
    fast;
    int t = 1;
    cin >> t;
    while(t--)
        solve();
    return 0;
}
