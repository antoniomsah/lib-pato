// Segment tree

template <class T>
struct segment_tree {
	T NEUT = T();

	int n;
	vector<T> seg;
 
	// O(n)
	segment_tree(vector<T> &v) : n(v.size()), seg(2*n) { 
		for (int i = 0; i < n; i++) seg[i+n] = v[i];
		for (int i = n-1; i; i--) seg[i] = seg[2*i] + seg[2*i+1];
	}
 
	// O(lgn)
	void update(int pos, T val) {
		for (seg[pos += n] = val; pos >>= 1;) 
			seg[pos] = seg[2*pos] + seg[2*pos+1];
	}

	// O(lgn)
	T query(int l, int r) {
		T tl = NEUT, tr = NEUT;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l&1) tl = tl + seg[l++];
			if (r&1) tr = tr + seg[--r];
		}
		return tl + tr;
	}
};