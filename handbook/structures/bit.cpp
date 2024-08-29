// BIT (Fenwick tree)
//
// Functions:
// 		query(l,r):	 sum of elements in range [l,r]
// 		update(i,x): 	 sums x to value in position i
// 		upper_bound(x):  smallest p st pref(p) > x
//
// Details: 0-indexed
//
// Complexity:
// 		build: 	     O(n)
// 		query: 	     O(lgn)
// 		update:	     O(lgn)
//		upper_bound: O(lgn)

template<typename T>
struct BIT {
	int n;
	vector<T> bit;
	BIT(int _n=0) : n(_n), bit(n + 1) {}
	BIT(vector<T> &v) : n(v.size()), bit(n + 1) {
		for (int i = 1; i <= n; i++) {
			bit[i] += v[i - 1];
			int j = i + (i & -i);
			if (j <= n) bit[j] += bit[i];
		}
	}
	void update(int i, T x) { // soma x na posicao i
		for (i++; i <= n; i += i & -i) bit[i] += x;
	}
	T pref(int i) { // soma [0, i]
		T ret = 0;
		for (i++; i; i -= i & -i) ret += bit[i];
		return ret;
	}
	T query(int l, int r) {  // soma [l, r]
		return pref(r) - pref(l - 1); 
	}
	int upper_bound(T x) {
		int p = 0;
		for (int i = __lg(n); i+1; i--) 
			if (p + (1<<i) <= n and bit[p + (1<<i)] <= x)
				x -= bit[p += (1 << i)];
		return p;
	}
};
