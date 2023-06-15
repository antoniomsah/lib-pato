template <typename T>
struct segtree {
	int n;
	vector<T> seg, lazy;
    
	T build(int p, int l, int r, vector<T> &v) {
		if(l == r) return seg[p] = v[l];
		int m = (l+r)/2;
		return seg[p] = build(2*p,l,m,v)+build(2*p+1,m+1,r,v);
	}
 
	segtree(vector<T> &v) : n(v.size()), seg(4*n), lazy(4*n) { 
		build(1,0,n-1,v); 
	}
    
	segtree(int n) : n(n), seg(4*n), lazy(4*n) {}
 
	void prop(int p, int l, int r){
		seg[p] += lazy[p]*(r-l+1);
		if(l!=r) lazy[2*p] += lazy[p], lazy[2*p+1] += lazy[p];
		lazy[p] = 0;
	}
 
	T update(int a, int b, int x, int p, int l, int r) {
		prop(p,l,r);
		if(a <= l and r <= b){
			lazy[p] += x;
			prop(p,l,r);
			return seg[p];
		}
		if(b < l or r < a) return seg[p];
		int m=(l+r)/2;
		return seg[p] = update(a,b,x,2*p,l,m)+update(a,b,x,2*p+1,m+1,r);
	}
 
	T query(int a, int b, int p, int l, int r){
		prop(p,l,r);
		if(a <= l and r <= b) return seg[p];
		if(b < l or r < a) return 0;
		int m = (l+r)/2;
		return query(a,b,2*p,l,m)+query(a,b,2*p+1,m+1,r);
	}
 
	void update(int a, int b, int x) { update(a,b,x,1,0,n-1); }
	T query(int a, int b) { return query(a,b,1,0,n-1); }
};
