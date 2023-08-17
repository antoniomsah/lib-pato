// Kuhn algorithm

struct Kuhn {
    int max_match;
    vector<int> mat;
    Kuhn(int n, int m, vector<vector<int>> &adj):mat(m,-1),max_match(0){
        vector<bool> vis(n);
        function<bool(int)> match = [&](int x){
            if(vis[x]) return false;
            vis[x] = true;
            for(auto v:adj[x]){
                if(mat[v] < 0 or match(mat[v])){
                    max_match += (mat[v] < 0);
                    mat[v] = x;
                    return true;
                }
            }
            return false;
        };
        for(int i=0;i<n;i++){
            fill(all(vis),0ll);
            match(i);
        }
    } 
};
