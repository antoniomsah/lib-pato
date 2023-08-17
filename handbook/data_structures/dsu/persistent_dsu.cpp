// Persistent DSU
//
// Description:
// 		Partial persistency, i.e., t must be incremented after
// 		each update
//
// Functions:
// 		find(a): finds a's set at version t
// 		unite(a,b,t): unites a and b at version t
//
// Complexity:
// 		find: O(lgn)
// 		unite: O(lgn)

struct dsu {
	vector<int> id, sz, ti;

	dsu(int n) : id(n), sz(n, 1), ti(n, -INF) { 
		iota(id.begin(), id.end(), 0); 
	}

	int find(int a, int t) { 
		if (id[a] == a or ti[a] > t) return a;
		return find(id[a], t);
	}

	void unite(int a, int b, int t) {
		a = find(a, t), b = find(b, t);
		if (a == b) return;
		if (sz[a] < sz[b]) swap(a, b);
		sz[a] += sz[b], id[b] = a, ti[b] = t;
	}
};
