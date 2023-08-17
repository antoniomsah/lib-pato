// Tarjan algorithm for strongly connected components
//
// Description: 
// 		Builds an array scc such that scc[u] = scc[v] 
// 		iff u and v are in the same component. And build an
// 		array sz such that sz[scc[u]] is the size of u's component.
//
// Complexity: O(n+m)

struct tarjan_scc {
	int nscc;
	vector<int> scc, sz;

	tarjan_scc(int n, vector<int> adj[]) : nscc(0), scc(n) {
		int t=0, sn=0;
		vector<int> disc(n,-1), low(n,-1), stk(n);

		function<void(int)> dfs = [&](int u) {
			disc[u] = low[u] = t++;
			stk[sn++] = u;
			for(auto v: adj[u]) {
				if(disc[v] == -1) dfs(v);
				low[u] = min(low[u], low[v]);
			}
			if(low[u] == disc[u]) {
				int v;
				sz.emplace_back(0);
				do {
					v = stk[--sn];
					scc[v] = nscc;
					sz[nscc]++;
					low[v] = INF;
				} while(u != v);
				nscc++;
			}
		};

		for(int i=0; i<n; i++) {
			if(disc[i] == -1) dfs(i);
		}
	}

	// Complexity: O(n+m)
	vector<vector<int>> condensed_graph(int n, vector<int> adj[]) {
		vector<vector<int>> adj_scc(nscc);
		for(int u=0; u<n; u++) {
			for(int v: adj[u]) {
				if(scc[v] != scc[u]) adj_scc[scc[u]].push_back(scc[v]);
			}
		}
		return adj_scc;
	}
};
