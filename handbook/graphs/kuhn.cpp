// Kuhn algorithm
//
// Description: computes a maximum matching in a bipartite graph
//
// Complexity: O(VE)
//
// Details: if not using add, the adjacency of only one side is needed


mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

struct Kuhn {
    int n,m; 
    vector<vector<int>> adj;
    vector<int> mu, mv;

    Kuhn(int n, int m) : 
        n(n), m(m), adj(n), mu(n,-1), mv(m,-1) {}

    void add(int u, int v) {
        adj[u].push_back(v);
    }

    int matching() {
		vector<bool> vis(n+m, false);

		function<bool(int)> dfs = [&](int u) {
			vis[u] = true;
			for(int v: adj[u]) if(!vis[n+v]) {
				vis[n+v] = true;
				if(mv[v] == -1 or dfs(mv[v])) {
					mu[u] = v, mv[v] = u;
					return true;
				}
			}
			return false;
		};

        int ret=0, aum=1;
        for(auto& u: adj) shuffle(u.begin(), u.end(), rng);
        while(aum) {
			fill(vis.begin()+n, vis.end(), false);
            aum=0;
            for(int u=0; u<n; u++) {
                if(mu[u] == -1 and dfs(u)) ret++, aum=1;
            }
        }
        return ret;
    }
};
