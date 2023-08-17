// Division trick
//
// Complexity: O(sqrt(n))

for(int l = 1, r; l <= n; l = r + 1) {
	r = n / (n / l);
	// n / i has the same value for l <= i <= r
}
