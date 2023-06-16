// BIT (Fenwick tree)
// query and update 1-indexed

template <typename T>
struct BIT{
    int n;
    vector<T> bit;
    BIT(int n):n(n+1),bit(n+1){}
    BIT(vector<int> &v):n(ssize(v)+1), bit(ssize(v)+1){
        for(int i=1;i<n;i++) bit[i] = v[i-1];
        for(int i=1;i<n;i++){
            int j = i+(i&-i);
            if(j<n) bit[j] += bit[i];
        }
    }
	T pref_query(int i){
	    T sum = 0;
	    for(;i;i-=i&-i) sum+=bit[i];
	    return sum;
	}
	T query(int a, int b){
	    return pref_query(b)-pref_query(a-1);
	}
	void update(int i, T delta){
	    for(;i<n;i+=i&-i) bit[i]+=delta;
	}
};
