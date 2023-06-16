// Persistent Segment Tree

template <typename T>
struct segtree{
    vector<T> st, L, R; 
    int n, rt;
	int new_node(T x, int l=0, int r=0){
		int nn = st.size();
		st.pb(x); L.pb(l); R.pb(r);
		return nn;
	}
	int build(vector<T> &v, int l, int r){
		if(l==r) return new_node(v[l]);
		int m=(l+r)/2, nl=build(v,l,m), nr=build(v,m+1,r);
		return new_node(st[nl]+st[nr],nl,nr);
	}
	segtree(int n): st(1,0),L(1,0),R(1,0),n(n){}
	int build(vector<T> &v){return rt = build(v,0,n-1);}
	int update(int p, T x, int k, int l, int r){
		int nn = new_node(st[k],L[k],R[k]);
		if(l == r){st[nn]=x;return nn;}
		int m = (l+r)/2;
		if(p <= m) L[nn] = update(p,x,L[nn],l,m);
		else R[nn] = update(p,x,R[nn],m+1,r);
		st[nn] = st[L[nn]] + st[R[nn]];
		return nn;
	}
	T query(int a, int b, int k, int l, int r){
		if(r < a or b < l) return 0;
		if(a <= l and r <= b) return st[k];
		int m = (l+r)/2;
		return query(a,b,L[k],l,m) + query(a,b,R[k],m+1,r);
	}
	int update(int p, int x, int k){return rt=update(p,x,k,0,n-1);}
	int update(int p, int x){return update(p,x,rt);}
	T query(int a, int b, int k){return query(a,b,k,0,n-1);};
};
