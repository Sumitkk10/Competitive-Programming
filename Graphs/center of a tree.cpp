int mx, node, n, degree[N], mx_lvl = 0, level[N];
queue<int> q;
set<int> centres;

void bfs(){
    while(!q.empty()){
        int node = q.front();
        q.pop();
        for(auto k : graph[node]){
            degree[k.first]--;
            if(degree[k.first] == 1){
                level[k.first] = level[node] + 1;
                q.push(k.first);
                mx_lvl = max(mx_lvl, level[k.first]);
            }
        }
    }
    for(int i = 0; i < n; ++i){
        if(level[i] == mx_lvl){
            // cout << k << ' ' << level[k] << '\n';
            centres.insert(i);
        }
    }
}
