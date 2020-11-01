ll seg_tree[4*N], a[N];

void build(int vertex, int l, int r){
	if(l == r)
		seg_tree[vertex] = a[l];
	else{
		int mid = (l + r) / 2;
		build(2 * vertex, l, mid);
		build((2 * vertex) + 1, mid + 1, r);
		seg_tree[vertex] = seg_tree[2*vertex] + seg_tree[(2*vertex) + 1];
	}
}

ll sum(int vertex, int l, int r, int x, int y){
	if(r < x || l > y) return 0;
	if(x <= l && r <= y)
		return seg_tree[vertex];
	int mid = (l + r) / 2;
	long long int ans = sum(2 * vertex, l, mid, x, y);
	long long int ans1 = sum((2 * vertex) + 1, mid + 1, r, x, y);
	return ans + ans1;
}

void update(int vertex, int l, int r, int idx, int x){
	if(r < idx || l > idx) return;
	if(l == r){
		seg_tree[vertex] += x; 
		return;
	}
	int mid = (l + r) / 2;
	update(2 * vertex, l, mid, idx, x);
	update((2 * vertex) + 1, mid + 1, r, idx, x);
	seg_tree[vertex] = seg_tree[2 * vertex] + seg_tree[(2 * vertex) + 1];
}
