// Splay tree for Link/Cut tree
// Details: is 1-indexed.
// Complexity: O(lgn) amortized

template <class T>
struct splay_tree {
	struct node {
		int child[2] = {0, 0}, p = 0;
		T sub = 0, vir = 0;	// sum of values in subtree, sum of values in virtual subtrees
		T path = 0, value = 0; // sum of path, node value
		bool rev = false;
	};

	vector<node> t;

	splay_tree(int sz) : t(sz+1) {}

	void push(int u) {
		if (not u or not t[u].rev) return;
		int l = t[u].child[0], r = t[u].child[1];
		swap(t[u].child[0], t[u].child[1]);
		t[l].rev ^= 1, t[r].rev ^= 1;
		t[u].rev = 0;
	}

	void pull(int u) {
		int l = t[u].child[0], r = t[u].child[1];
		push(l); push(r);
		t[u].path = t[l].path + t[u].value + t[r].path;
		t[u].sub = t[l].sub + t[u].vir + t[u].value + t[r].sub;
	}

	// attaches u to v
	void attach(int u, int v, bool d) {
		t[u].child[d] = v; t[v].p = u; pull(u);
	}

	// -1 -> has no parent, 0 -> left child, 1 -> right child
	int dir(int u) {
		int p = t[u].p;
		if (not p) return -1;
		if (t[p].child[0] == u) return 0;
		return (t[p].child[1] == u? 1: -1);
	}

	void rotate(int u) {
		int p = t[u].p, pp = t[p].p,
			du = dir(u), dp = dir(p);
		attach(p, t[u].child[!du], du);
		attach(u, p, !du);
		if (~dp) attach(pp, u, dp);
		t[u].p = pp;
	}

	void splay(int u) {
		push(u);
		while (~dir(u)) {
			int p = t[u].p;
			assert(u != p);
			push(t[p].p); push(p); push(u); 
			int du = dir(u), dp = dir(p);
			if (~dp) rotate(du == dp? p: u);
			rotate(u);
		}
	}
};