// Bipartite Disjoint Union Set (bipartite DSU)
//
// Description:
// 		Unites two vertices and finds a vertex's component.
// 		Answers if a component is bipartite 
// 		(bip[a] = 1 -> a's component is bipartite)
//
// Functions:
// 		find(a): finds a's component
// 		color(a): colorates a's component
// 		unite(a,b): unites a and b
//
// Complexity:
// 		find: O(lgn)
// 		color: O(lgn)
// 		unite: O(lgn)

struct dsu {
	vector<int> id, sz, bip, c;

	dsu(int n) : id(n), sz(n, 1), bip(n, 1), c(n) { 
		iota(id.begin(), id.end(), 0); 
	}

	int find(int a) { return a == id[a] ? a : find(id[a]); }
	int color(int a) { return a == id[a] ? c[a] : c[a] ^ color(id[a]); }

	void unite(int a, int b) {
		bool change = color(a) == color(b);
		a = find(a), b = find(b);
		if (a == b) {
			if (change) bip[a] = 0;
			return;
		}
		
		if (sz[a] < sz[b]) swap(a, b);
		if (change) c[b] = 1;
		sz[a] += sz[b], id[b] = a, bip[a] &= bip[b];
	}
};
