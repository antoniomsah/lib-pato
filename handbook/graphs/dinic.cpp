/**
 * Dinitz's algorithm for finding maximum flows.
 *
 * Complexity: O(n^2m) (O(m sqrt(n)) on unit networks)
 **/


template <typename T>
struct Dinic {
	struct Edge {
		int to, cap, flow;
		Edge(int _to, int _cap) :
			to(_to), cap(_cap), flow(0) {}
	};

	int s,t;
	vector<T> dist, ptr, q;
	vector<vector<int>> adj;
	vector<Edge> edges;

	Dinic(int _s, int _t, int n) : 
		s(_s), t(_t), dist(n), ptr(n), adj(n), q(n) {}

	void add_edge(int u, int v, int cap){
		edges.push_back({v,cap});
		adj[u].push_back(edges.size()-1);
		edges.push_back({u,0});
		adj[v].push_back(edges.size()-1);
	}

	bool bfs() {
		fill(dist.begin(), dist.end(), -1);
		int st=0,ed=0;
		q[ed++] = s;
		dist[s] = 0;
		while(st<ed){
			int u = q[st++];
			for(int i=0; i<adj[u].size(); i++){
				int idx = adj[u][i], v = edges[idx].to;
				if(dist[v] == -1 and edges[idx].cap > edges[idx].flow){
					dist[v] = dist[u]+1;
					q[ed++] = v;
				}
			}
		}
		return dist[t] != -1;
	}

	T dfs(int u, T f=INF){
		if(u == t or f == 0) return f;
		for(int &i=ptr[u]; i<adj[u].size(); i++){
			int idx = adj[u][i], v = edges[idx].to;
			if(dist[u]+1 == dist[v] and edges[idx].cap > edges[idx].flow){
				int df = dfs(v, min(f,edges[idx].cap-edges[idx].flow));
				if(df>0){
					edges[idx].flow += df;
					edges[idx^1].flow -= df;
					return df;
				}
			}
		}
		return 0;
	}

	T flow() {
		T flow=0;
		while(bfs()){
			fill(ptr.begin(), ptr.end(), 0);
			while(T add_flow=dfs(s)) flow += add_flow;
		}
		return flow;
	}
};
