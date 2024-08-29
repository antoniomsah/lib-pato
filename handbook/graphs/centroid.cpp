// Centroid decomposition

namespace centroid {
	const int MAXN = 2e5+10;
	
	vector<int> sz(MAXN, 1);
	vector<bool> removed(MAXN);
	vector<vector<int>> adj(MAXN);

	int set_sizes(int u, int p = -1) {
		sz[u] = 1;
		for (int v: adj[u]) if (v != p and not removed[v]) {
			sz[u] += set_sizes(v, u);
		}
		return sz[u];
	}

	int get_centroid(int u, int size) {
		for (int v: adj[u]) if (sz[v] < sz[u]) {
			if (sz[v] > size/2) return get_centroid(v, size);
		}
		return u;
	}

	// For example
	vector<int> dists(MAXN);

	int solve(int root, int k) {
		int c = get_centroid(root, set_sizes(root));
		removed[c] = true;

		// Answer in linear time here
		// Example: number of paths of length k

		int res = 0;
		queue<int> add, rem;
		function<void(int, int, int)> dfs = [&](int u, int dep, int p) {
			if (k >= dep) res += dists[k-dep];
			add.push(dep); rem.push(dep);
			for (int v: adj[u]) if (v != p and not removed[v]) {
				dfs(v, dep+1, u);
			}
		};

		dists[0] = 1;
		for (int v: adj[c]) if (not removed[v]) {
			dfs(v, 1, -1);
			while (add.size()) {
				int d = add.front(); add.pop();
				dists[d] += 1;
			}
		}
	
		while (rem.size()) {
			int d = rem.front(); rem.pop();
			dists[d] -= 1;
		}

		// Example end.

		for (int v: adj[c]) if (not removed[v]) {
			res += solve(v, k);
		}
		return res;
	}
};