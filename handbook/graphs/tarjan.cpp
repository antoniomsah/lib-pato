// Tarjan

    stack<int> s;
    vector<int> vis(n), comp(n), id(n);
    int t = 0;
    function<int(int)> dfs = [&](int x){
        int lo = id[x] = t++;
        s.push(x);
        vis[x] = 2;
        for(int v:adj[x]){
            if(!vis[v]) lo = min(lo, dfs(v));
            else if(vis[v] == 2) lo = min(lo, id[v]);
        }
        if(lo == id[x]) while(true){
            int v = s.top(); s.pop();
            vis[v] = 1, comp[v] = x;
            if (v == x) break;
        }
        return lo;
    };
    for(int i=0;i<n;i++) if(!vis[i]) dfs(i);
