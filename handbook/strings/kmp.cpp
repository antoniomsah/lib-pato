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
