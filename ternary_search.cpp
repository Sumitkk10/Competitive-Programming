// finds the maximum value if the function first increases then decreases or it first decreases and then increases (unimodal)

int ternary_search(int str, int l, int r){
    while(r - l > 2){
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;
        int x = f(str, m1), y = f(str, m2);
        if(x < y)
            l = m1;
        else
            r = m2;
    }
    int mx = 0;
    for(int i = l; i <= r; ++i)
        mx = max(mx, f(str, i));
    return mx;
}
