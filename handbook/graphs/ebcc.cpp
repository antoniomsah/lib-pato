// Tarjan algorithm for edge-biconnected components
//
// Description:
// 		Builds an array ebcc such that ebcc[u] = ebcc[v] iff
// 		u and v are in the same component. 
//
// 		Builds an array sz such that sz[ebcc[u]] is the size
// 		of u's component.
//
// Complexity: O(n+m)

struct tarjan_ebcc {
	int nebcc;
	vector<int> ebcc, sz;

	tarjan_ebcc(int n, vector<int> adj[]) : nebcc(0), ebcc(n) {
		int t=0, sn=0;
		vector<int> disc(n,-1), low(n,-1), stk(n);

		function<void(int,int)> dfs = [&](int u, int p) {
			disc[u] = low[u] = t++;
			stk[sn++] = u;
			for(auto v: adj[u]) {
				if(disc[v] == -1) {
					dfs(v,u);
					low[u] = min(low[u], low[v]);
				}
				else if(v != p) low[u] = min(low[u], disc[v]);
			}
			if(low[u] == disc[u]) {
				int v;
				sz.emplace_back(0);
				do {
					v = stk[--sn];
					ebcc[v] = nebcc;
					sz[nebcc]++;
				} while(u != v);
				nebcc++;
			}
		};

		for(int i=0; i<n; i++) {
			if(disc[i] == -1) dfs(i,i);
		}
	}

	vector<vector<int>> condensed_graph(int n, vector<int> adj[]) {
		vector<vector<int>> adj_ebcc(nebcc);
		for(int u=0; u<n; u++) {
			for(int v: adj[u]) {
				if(ebcc[v] != ebcc[u]) adj_ebcc[ebcc[u]].push_back(ebcc[v]);
			}
		}
		return adj_ebcc;
	}
};
