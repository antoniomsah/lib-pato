// DSU with rollback
//
// Description:
// 		Allows the DSU to return to previous versions.
// 		Every update is added to the stack.
//
// Functions:
// 		find(a): finds a's component
// 		unite(a,b): unites a and b
// 		checkpoint: saves the current state of all variables
// 		rollback: returns all variables to last checkpoint
//
// Complexity:
//		save: O(1)
//		checkpoint: O(1)
// 		find: O(lgn)
// 		unite: O(lgn)
// 		rollback: O(m), m is the number of changes after last checkpoint

struct dsu {
	vector<int> id, sz;
	stack<stack<pair<int&, int>>> st;

	dsu(int n) : id(n), sz(n, 1) { 
		iota(id.begin(), id.end(), 0), st.emplace(); 
	}
		
	void save(int &x) { st.top().emplace(x, x); }

	void checkpoint() { st.emplace(); }
	
	void rollback() {
		while(st.top().size()) {
			auto [end, val] = st.top().top(); st.top().pop();
			end = val;
		}
		st.pop();
	}

	int find(int a) { return a == id[a] ? a : find(id[a]); }

	void unite(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return;
		if (sz[a] < sz[b]) swap(a, b);
		save(sz[a]), save(id[b]);
		sz[a] += sz[b], id[b] = a;
	}
};
