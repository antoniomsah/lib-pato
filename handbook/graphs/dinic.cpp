/**
 * Dinitz's algorithm for finding maximum flows.
 *
 * Complexity: O(n^2m) (O(m sqrt(n)) on unit networks)
 **/

template <typename T>
struct Dinic {
	struct Edge {
		int to;
		T cap, flow;
		Edge(int _to, T _cap) :
			to(_to), cap(_cap), flow(0) {}
	};

	int s,t;
	vector<int> nxt, ptr, frst, dist, q;
	vector<Edge> edges;

	Dinic(int _s, int _t, int n) : 
		s(_s), t(_t), dist(n), frst(n,-1), q(n) {}

	void add(int u, int v, T cap){
		edges.emplace_back(v,cap);
		nxt.push_back(frst[u]);
		frst[u] = edges.size()-1;

		edges.emplace_back(u,0);
		nxt.push_back(frst[v]);
		frst[v] = edges.size()-1;
	}

	bool bfs() {
		fill(dist.begin(), dist.end(), -1);
		int st=0,ed=0;
		q[ed++] = s;
		dist[s] = 0;
		while(st<ed){
			int u = q[st++];
			for(int e=frst[u]; e != -1; e = nxt[e]) {
				int v = edges[e].to;
				if(dist[v] == -1 and edges[e].cap > edges[e].flow){
					dist[v] = dist[u]+1;
					q[ed++] = v;
				}
			}
		}
		return dist[t] != -1;
	}

	T dfs(int u, T f=INF){
		if(u == t or f == 0) return f;
		for(int &e=ptr[u]; e != -1; e=nxt[e]) {
			int v = edges[e].to;
			if(dist[u]+1 == dist[v] and edges[e].cap > edges[e].flow){
				int df = dfs(v, min(f,edges[e].cap-edges[e].flow));
				if(df>0){
					edges[e].flow += df;
					edges[e^1].flow -= df;
					return df;
				}
			}
		}
		return 0;
	}

	T flow() {
		T flow=0;
		while(bfs()){
			ptr=frst;
			while(T add_flow=dfs(s)) flow += add_flow;
		}
		return flow;
	}
};
