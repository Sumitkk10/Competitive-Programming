// Minimum no of semesters needed to complete education..

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define ll long long int
#define ld long double
using namespace std;
const int N = 12;
const int MOD = 1e9 + 7;
ll n, m, indegree[N], LPD[N];
vector<ll> graph[N];
bool vis[N];
queue<int> q;

void indegre(int source){
    vis[source] = true;
    for(auto i : graph[source]){
        indegree[i]++;
        if(!vis[i])
            indegre(i);
    }
}

void DAG(){
    while(!q.empty()){
        long long int node = q.front();
        q.pop();
        for(auto edge : graph[node]){
            if(!vis[edge]){
                indegree[edge]--;
                if(indegree[edge] == 0){
                    q.push(edge);
                    vis[edge] = true;
                }
                LPD[edge] = max(LPD[(ll) edge], LPD[node] + 1);
            }
        }
    }
}

int main(){
    fast;
    cin >> n >> m;
    for(int i = 1; i <= m; ++i){
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }
    for(int i = 1; i <= n; ++i){
        if(!vis[i])
            indegre(i);
    }
    memset(vis, 0, sizeof(vis));
    for(int i = 1; i <= n; ++i){
    	// cout << indegree[i] << " ";
        if(indegree[i] == 0){
            q.push(i);
            vis[i] = true;
        }
    }
    DAG();
   	map<long long int, long long int> mp;
   	for(long long int i = 1; i <= n; ++i){
   		mp[LPD[i]]++;
   		// cout << LPD[i] << " ";
   	}
   	cout << mp.size() << "\n";
    return 0;
}
