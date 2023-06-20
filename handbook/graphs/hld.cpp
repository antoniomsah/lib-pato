/**
 * Heavy-light decomposition for vertices.
 *
 * Description:
 * 		Allows range queries and updates on trees. Template uses
 * 		lazy segment tree, keep in mind that if structure is changed
 * 		then the complexities change.
 *
 * Functions:
 * 		query_path(a,b): 	 sum of elements in the path a -> b
 * 		update_path(a,b,x):	 sums x to elements in path a -> b
 * 		query_subtree(a):	 sum of elements in the subtree of a
 * 		update_subtree(a,x): sums x to elements in the subtree of a
 *
 * Complexity:
 * 		query_path:  	O(lg^2 n)
 * 		update_path: 	O(lg^2 n)
 * 		query_subtree: 	O(lgn)
 * 		update_subtree: O(lgn)
 **/

const int MAXN = 6e5;

namespace hld {
	segtree<long long> seg;
	vector<int> h(MAXN), v(MAXN), p(MAXN), pos(MAXN), sz(MAXN), peso(MAXN);

	void build(int root, int n, vector<int> adj[]) {
		int t=0;

		function<void(int,bool)> dfs = [&](int u, bool f) {
			v[pos[u]=t++] = peso[u]; 
			sz[u] = 1;
			for(auto &v: adj[u]) {
				if(v == p[u]) continue;
				p[v] = u;
				h[v] = (v == adj[u][0]? h[u]: v);
				dfs(v,f);
				sz[u] += sz[v];
				if(sz[v] > sz[adj[u][0]] or adj[u][0] == p[v]) {
					swap(v, adj[u][0]);
				}
			}
			if(u == root and f) dfs(u,t=false);
		};

		dfs(root,true);
		seg = segtree<long long>(t,v);
	}

	long long query_path(int a, int b) {
		if(pos[a] < pos[b]) swap(a,b);
		if(h[a] == h[b]) return seg.query(pos[a],pos[b]);
		return seg.query(pos[h[a]], pos[a]) + query_path(p[h[a]], b);
	}

	void update_path(int a, int b, int x) {
		if(pos[a] < pos[b]) swap(a,b);
		if(h[a] == h[b]) return seg.update(pos[b],pos[a],x);
		seg.update(pos[h[a]], pos[a], x); 
		update_path(p[h[a]], b, x);
	}

	long long query_subtree(int a) {
		return seg.query(pos[a], pos[a]+sz[a]-1);
	}

	void update_subtree(int a, int x) {
		seg.update(pos[a], pos[a]+sz[a]-1, x);
	}
};
