/**
 * Sparse table
 *
 * Functions:
 * 		query(l,r): minimum element in range [l,r]
 *
 * Complexity:
 * 		build: O(nlgn)
 * 		query: O(1)
 **/

template <typename T>
struct sparse {
    int n;
    vector<vector<T>> m;

    sparse(vector<T> &v) : n(v.size()) {
		int lg = 32 - __builtin_clz(n);
        m.assign(lg,vector<T>(n));
		for(int i=0;i<n;i++) m[0][i] = v[i];
		for(int j=1;(1<<j)<=n;j++) {
			for(int i=0;i+(1<<j)<=n;i++) {
				m[j][i] = min(m[j-1][i], m[j-1][i+(1<<(j-1))]);
			}
		}
	}

	T query(int l, int r) {
		int j = 31 - __builtin_clz(r-l+1);
		return min(m[j][l], m[j][r-(1<<j)+1]);
	}
};
