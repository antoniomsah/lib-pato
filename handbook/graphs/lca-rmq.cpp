// Lowest common ancestor using RMQ
//
// Description: finds the LCA in O(1) using RMQ

namespace LCA {
	vector<int> dep, pos, inv;
	RMQ<pair<int,int>> rmq;

	void build(int root, const vector<vector<int>>& adj) {
		dep.resize(2 * adj.size()); 
		inv.resize(2 * adj.size());
		pos.resize(adj.size());

		int t = 0;
		function<void(int, int, int)> dfs = [&](int u, int d, int p) {
			inv[t] = u, pos[u] = t, dep[t++] = d;
			for (int v: adj[u]) if (v != p) {
				dfs(v, d+1, u);
				inv[t] = u, dep[t++] = d;
			}
		};
		dfs(root, 0, -1);
		rmq = RMQ(dep);

		vector<pair<int,int>> vals(t);
		for (int i = 0; i < t; i++) {
			vals[i] = {dep[i], i};
		}
		rmq = RMQ(vals);
	}

	int lca(int u, int v) {
		if (pos[u] > pos[v]) swap(u, v);
		return inv[rmq.query(pos[u], pos[v])];
	}

	int dist(int u, int v) {
		return dep[pos[u]] + dep[pos[v]] - 2 * dep[pos[lca(u, v)]];
	}
}