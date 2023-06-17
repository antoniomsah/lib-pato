// Persistent Segment Tree

template <typename T>
struct pseg{
	const int LIM = 1e7;
    int n, rt, nxt;
    vector<T> seg; 
	vector<int> L, R;
	pseg(int n): seg(LIM),L(LIM),R(LIM),n(n),nxt(0){}
	int new_node(T x, int l=0, int r=0){
		int nn = nxt++;
		seg[nn] = x; L[nn] = l; R[nn] = r;
		return nn;
	}
	int build(vector<T> &v, int l, int r){
		if(l==r) return new_node(v[l]);
		int m=(l+r)/2, nl=build(v,l,m), nr=build(v,m+1,r);
		return new_node(seg[nl]+seg[nr],nl,nr);
	}
	int build(vector<T> &v){return rt = build(v,0,n-1);}
	int update(int p, T x, int k, int l, int r){
		int nn = new_node(seg[k],L[k],R[k]);
		if(l == r){seg[nn]=x;return nn;}
		int m = (l+r)/2;
		if(p <= m) L[nn] = update(p,x,L[nn],l,m);
		else R[nn] = update(p,x,R[nn],m+1,r);
		seg[nn] = seg[L[nn]] + seg[R[nn]];
		return nn;
	}
	T query(int a, int b, int k, int l, int r){
		if(r < a or b < l) return 0;
		if(a <= l and r <= b) return seg[k];
		int m = (l+r)/2;
		return query(a,b,L[k],l,m) + query(a,b,R[k],m+1,r);
	}
	int update(int p, T x, int k){return rt=update(p,x,k,0,n-1);}
	int update(int p, T x){return update(p,x,rt);}
	T query(int a, int b, int k){return query(a,b,k,0,n-1);};
};
