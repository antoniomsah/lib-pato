template<typename T> 
struct Matrix : vector<vector<T>> {
	int n,m;
    Matrix(const vector<vector<T>>& c) : vector<vector<T>>(c), n(c.size()), m(c[0].size()) {}
	Matrix(int n, int m) : vector<vector<T>>(n,vector<T>(m,0)),n(n),m(m){}
    Matrix(const initializer_list<initializer_list<T>>& c) {
		vector<vector<T>> val;
		for(auto& i:c) val.push_back(i);
		*this = Matrix(val);
	}
	Matrix operator*(Matrix& r) {
		assert(m == r.n);
		Matrix M(n, r.m);
		for(int i=0;i<n;i++) 
            for(int k=0;k<m;k++)
			    for(int j=0;j<r.m;j++)
				    M[i][j] += (*this)[i][k]*r[k][j];
		return M;
	}
	Matrix operator^(ll e){
		Matrix M(n,n);
        for(int i=0;i<n;i++) M[i][i] = 1;
        for(Matrix at=*this;e;e/=2,at=at*at)
			if(e&1) M = M*at;
		return M;
	}
};
