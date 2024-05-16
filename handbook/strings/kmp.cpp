// Knuth-Morris-Pratt algorithm (KMP)
//
// Description: 
//		The prefix function, p[i] is the longest suffix that ends at i
//		that is also a suffix.
// 
// Complexity: O(n)

template<typename T>
vector<int> kmp(int sz, const T s[]) {
	vector<int> p(sz);
	for(int i=1;i<sz;i++) {
		int &j = p[i];
		for(j=p[i-1];j>0 && s[i]!=s[j];j=p[j-1]);
		if(s[i] == s[j]) j++;
	}
	return p;
}

vector<vector<int>> automaton(string s) {
    s += '#';
    int n = (int)s.size();
    auto p = kmp(s.size(), s.data());
    vector<vector<int>> aut(n,vector<int>(26,0));
    for(int i=0;i<n;i++) {
        for(int c=0;c<26;c++) {
            if(i>0 && 'a'+c != s[i]) aut[i][c] = aut[p[i-1]][c];
            else aut[i][c] = i + ('a' + c == s[i]);
        }
    }
    return aut;
}
