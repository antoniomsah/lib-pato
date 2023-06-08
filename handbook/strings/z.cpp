/**
 * Z-function. 
 *
 * z[i]: is the longest suffix that starts in i that is also
 * a suffix that starts at 0.
 *
 * Complexity: O(n)
 **/

template<typename T>
vector<int> z_function(int n, const T s[]) {
	vector<int> z(n);
	int x = 0, y = 0;
	for (int i = 1; i < n; i++) {
		z[i] = max(0,min(z[i-x],y-i+1));
		while (i+z[i] < n && s[z[i]] == s[i+z[i]]) {
			x = i; y = i+z[i]; z[i]++;
		}
	}
	return z;
}
