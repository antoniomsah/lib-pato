/**
 * BIT (Fenwick tree)
 * 
 * Description:
 * 		Query and update are 1-indexed
 *
 * Functions:
 * 		query(l,r):	 sum of elements in range [l,r]
 * 		update(i,x): sums x to value in position i
 *
 * Complexity:
 * 		build: 	O(n)
 * 		query: 	O(lgn)
 * 		update:	O(lgn)
 **/

template <typename T>
struct BIT{
	int n;
	vector<T> bit;

	BIT(int n):n(n+1),bit(n+1){}
	BIT(vector<int> &v) : n(ssize(v)+1), bit(ssize(v)+1) {
		for(int i=1;i<n;i++) bit[i] = v[i-1];
		for(int i=1;i<n;i++) {
			int j = i+(i&-i);
			if(j<n) bit[j] += bit[i];
		}
	}

	T pref_query(int i) {
		T sum = 0;
		for(;i;i-=i&-i) sum+=bit[i];
		return sum;
	}

	T query(int l, int r) {
		return pref_query(r)-pref_query(l-1);
	}

	void update(int i, T x) {
		for(;i<n;i+=i&-i) bit[i]+=x;
	}
};
