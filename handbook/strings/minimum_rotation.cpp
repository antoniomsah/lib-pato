// Lexicographically smallest rotation of a string
// O(n)

int minimum_rotation(string s) {
	int a = 0, n = s.size(); s += s;
	for (int b = 0; b < n; b++) for (int k = 0; k < n; k++) {
		if (a+k == b or s[a+k] < s[b+k]) { b += max<int>(0, k-1); break; }
		if (s[a+k] > s[b+k]) { a = b; break; }
	}
	return a;
}