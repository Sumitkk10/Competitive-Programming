/*
if you want to find the minimum number the frequency of numbers lower than that is < val then you can do it in logn.
*/
void upd(int node, int val){
    for(int i = node; i < N; i += (i & -i))
        fenwick[i] += val;
}
 
int get(int val){
    int cur = 0, sum = 0;
    for(int i = 20; i >= 0; --i){
        if(cur + (1ll << i) <= n and sum + fenwick[cur + (1ll << i)] < val){
            sum += fenwick[cur + (1ll << i)];
            cur += (1ll << i);
        }
    }
    return cur + 1;
}
