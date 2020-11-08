int nextgreater[n];
for(int i = 0; i < n; ++i){
	while(!stk.empty() && a[stk.top()] < a[i]){
		nextgreater[stk.top()] = i;
		stk.pop();
	}
	stk.push(i);
}
while(!stk.empty()){
	nextgreater[stk.top()] = -1;
	stk.pop();
}
