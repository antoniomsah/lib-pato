// Disjoint Set Union (DSU)
//
// Functions:
// 		find(a): finds a's set
// 		unite(a,b): unites a and b
//
// Complexity:
// 		constructor: O(n)
// 		find:  O(1) amortized
// 		unite: O(1) amortized

struct dsu {
	vector<int> id, sz;

	dsu(int n) : id(n), sz(n, 1) { iota(id.begin(), id.end(), 0); }

	int find(int a) { return a == id[a] ? a : id[a] = find(id[a]); }

	void unite(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return;
		if (sz[a] < sz[b]) swap(a, b);
		sz[a] += sz[b], id[b] = a;
	}
};
