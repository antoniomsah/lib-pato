// 2-SAT algorithm

// Description:
// 		Decideds if a 2-SAT instance has a solution and
// 		finds a valid solution (if possible).
//
// Details:
// 		'sz' in the constructor and reset function represents
// 		the number of clausures.
//
// Complexity:
// 		solve() and reset(n) are O(n).

struct TwoSAT {
	int n, c, t;
	vector<vector<int>> adj, adjr;
	vector<int> topo, vis, comp, value;

	TwoSAT(int sz) : n(2*sz), adj(n), adjr(n), topo(n), vis(n), comp(n), value(n) {
		reset(sz);
	}

	void reset(int sz) {
		n = 2*sz;
		for(int i = 0; i < n; i++){
			topo[i] = vis[i] = comp[i] = value[i] = 0;
			adj[i].clear();
			adjr[i].clear();
		}
		t = 0;
		c = 1;
	}

	int to_vertex(int i) {
		if(i > 0) return (i - 1)<<1;
		return to_vertex(-i) + 1;
	}

	void add(int i, int j) { // add clause (i or j)
		int vi = to_vertex(i);
		int vj = to_vertex(j);
		adj[vi^1].push_back(vj);
		adj[vj^1].push_back(vi);
		adjr[vj].push_back(vi^1);
		adjr[vi].push_back(vj^1);
	}

	void add_true(int i) {	// add clause (i)
		add(i, i);
	}

	void add_false(int i) {	// add clause (neg i)
		add(-i, -i);
	}

	void add_xor(int i, int j) {	// add clause (i xor j)
		add(i, j);
		add(-i, -j);
	}

	void add_xnor(int i, int j) { // add clause (i xnor j)
		add(i, -j);
		add(-i, j);
	}

	void dfs1(int v) {
		vis[v] = 1;
		for(auto x : adj[v]) if(vis[x] == 0) dfs1(x);
		topo[t++] = v;
	}	

	void dfs2(int v) {
		comp[v] = c;
		for(auto x : adjr[v]) if(comp[x] == 0) dfs2(x);
	}

	bool solve() { 
		for(int i = 0; i < n; i++)
			if(vis[i] == 0) dfs1(i);
		for(int i = n - 1; i >= 0; i--) {
			if(comp[topo[i]] == 0) {
				dfs2(topo[i]);
				c++;
			}
		}
		for(int i = 0; i < n; i+=2) {
			if(comp[i] == comp[i^1])
				return false;
			else {
				value[i] = (comp[i] < comp[i^1]) ? 0 : 1;
				value[i^1] = 1 - value[i];
			}
		}
		return true;
	}

	bool get_value(int i) {
		return value[to_vertex(i)];
	}

	void print() {
		for(int i = 0; i < n; i += 2) {
			if(i != 0) cout << ' ';
			cout << value[i];
		}
		cout << endl;
	}
};
