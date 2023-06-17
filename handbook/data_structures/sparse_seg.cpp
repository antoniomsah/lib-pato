template <typename T>
struct sseg{
    const int LIM = 1e7;
    const int N = 1e9;
    vector<T> seg, lazy;
    vector<int> L,R;
    int nxt;
    sseg():seg(LIM),lazy(LIM),L(LIM),R(LIM),nxt(2){}
    int get_l(int i){
        if(!L[i]) L[i] = nxt++;
        return L[i];
    }
    int get_r(int i){
        if(!R[i]) R[i] = nxt++;
        return R[i];
    }
    void prop(int p, int l, int r){
        seg[p] += lazy[p]*(r-l+1);
        if(l!=r) lazy[get_l(p)]+=lazy[p], lazy[get_r(p)]+=lazy[p];
        lazy[p] = 0;
    }
    T update(int a, int b, T x, int p, int l, int r){
        prop(p,l,r);
        if(a <= l and r <= b){
            lazy[p] += x;
            prop(p,l,r);
            return seg[p];
        }
        if(b < l or r < a) return seg[p];
        int m = (l+r)/2;
        return seg[p] = update(a,b,x,get_l(p),l,m) + update(a,b,x,get_r(p),m+1,r);
    }
    T query(int a, int b, int p, int l, int r){
        prop(p,l,r);
        if(a <= l and r <= b) return seg[p];
        if(b < l or r < a) return 0;
        int m = (l+r)/2;
        return query(a,b,get_l(p),l,m)+query(a,b,get_r(p),m+1,r);
    }
    void update(int a, int b, T x){update(a,b,x,1,0,N-1);};
    T query(int a, int b){return query(a,b,1,0,N-1);};
};
