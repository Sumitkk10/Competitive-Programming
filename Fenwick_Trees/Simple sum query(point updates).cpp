// remember this is 1-based
// get() gives the sum of the values from 1 to i(including the ith element)


void update(int node, int val){
    for(int i = node; i <= n; i += (i & -i))
        fenwick[i] += val;
}

long long get(int node){
    long long ans = 0;
    for(int i = node; i >= 1; i -= (i & -i))
        ans += fenwick[i];
    return ans;
}
