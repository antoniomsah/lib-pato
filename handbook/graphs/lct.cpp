// Link/cut tree
// Description: manages dynamic connectivity and handles
// path sum queries and subtree sum queries
// Details: is 1-indexed.
// Complexity: O(lgn) amortized

struct link_cut_tree : splay_tree<ll> {
	using T = ll;

	link_cut_tree(int size) : splay_tree<T>(size) {}

	int access(int u) {
		int v = u, last = 0;
		for (; v; last = v, v = t[v].p) {
			splay(v); 
			// removing right child
			int &r = t[v].child[1];
			t[v].vir += t[r].sub;
			t[v].vir -= t[last].sub;
			r = last; pull(v);
		}
		return splay(u), last;
	}

	void make_root(int u) {
		access(u); t[u].rev ^= 1; 
	}

	void link(int u, int v) {
		make_root(u); access(v);
		t[v].vir += t[u].sub;
		t[u].p = v; pull(v);
	}

	void cut(int u, int v) {
		make_root(u); access(v);
		t[u].p = 0, t[v].child[0] = 0;
		pull(v);
	}

	int find_root(int u) {
		access(u); push(u);
		while (t[u].child[0]) {
			u = t[u].child[0]; push(u);
		}
		return u;
	}

	int lca(int u, int v) {
		if (u == v) return u;
		access(u); 
		int ret = access(v);
		return (t[u].p? ret: 0);
	}

	bool same(int u, int v) {
		return lca(u, v);
	}

	// sum of vertices in u's subtree when
	// v is a root
	T subtree(int u, int v) {
		make_root(v); access(u); return t[u].value + t[u].vir;
	}

	// sum of values in path [u...v]
	T path(int u, int v) {
		make_root(u); access(v); return t[v].path;
	}

	void update(int u, int x) {
		access(u); t[u].value = x; pull(u);
	}

	// jumps k vertices in path [u...v]
	// t[x].sub MUST be x's subtree size
	int jump(int u, int v, int k) {
		make_root(u); access(v); 
		if (k > t[u].sub) return 0;
		while (true) {
			push(v); pull(v);
			int rsz = 0;
			if (t[v].child[1]) rsz = t[t[v].child[1]].sub;

			if (k < rsz) {
				v = t[v].child[1];
			} else if (k == rsz) {
				break;
			} else {
				k -= rsz+1;
				v = t[v].child[0];
			}
		}
		return splay(v), v;
	}
};