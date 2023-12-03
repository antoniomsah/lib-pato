// XOR basis
//
// Description: 
// 		builds a basis in \Integers_2 that spans the
// 		vectors inserted.
//
// 		think of integers as vectors in \Integers_2,
// 		i.e., 4 -> (1,0,0).
//
// Complexity: O(SZ), unless stated otherwise


template <const int SZ>
struct XorBasis {
	int base[SZ];

	XorBasis() { memset(base, 0, sizeof base); }

	bool bit_on(int x, int i) {
		return (x&(1LL<<i));
	}

	void insert(int v) {
		for (int i = SZ-1; i >= 0; i--) {
			if (bit_on(v, i)) {
				if (!base[i]) {
					base[i] ^= v; 
					return;
				}
				v ^= base[i];
			}
		}
	}

	// merges two basis in O(SZ^2)
	void merge(XorBasis &b) {
		for (int i = SZ-1; i >= 0; i--) {
			if (b.base[i]) insert(b.base[i]);
		}
	}

	// checks if v can be achieved
	bool check(int v) {
		int x = 0;
		for (int i = SZ-1; i >= 0; i--) if (base[i]) {
			if (bit_on(x, i) != bit_on(v, i)) {
				x ^= base[i];
			}
		}
		return (x == v);
	}

	// returns the maximum value
	int max() {
		int value = 0;
		for (int i = SZ-1; i >= 0; i--) if (!bit_on(value, i)) {
			value ^= base[i];
		}
		return value;
	}
};
