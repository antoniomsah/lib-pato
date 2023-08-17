// String hashing
//
// Description: 
//  	A data structure that maps a string to a number

// Functions:
//		str_hash: hash in O(|S|)
//		operator(): the number representing substring s[l,r] in O(1)

// Details:
//		To use more than one prime, you may use long long, __int128 or array<int>
//		Large primes: 1000015553, 1000028537, 1000041323, 100663319, 201326611
//		Smaller primes: 50331653, 12582917, 6291469, 3145739, 1572869

template<int MOD> 
struct str_hash {
    static int P;
    vector<ll> h, p;
    str_hash () {}
    str_hash(string s) : h(s.size()), p(s.size()) {
        p[0] = 1, h[0] = s[0];
        for (int i = 1; i < s.size(); i++)
            p[i] = p[i - 1]*P%MOD, h[i] = (h[i - 1]*P + s[i])%MOD;
    }
    ll operator()(int l, int r) { // hash s[l...r]
        ll hash = h[r] - (l ? h[l - 1]*p[r - l + 1]%MOD : 0);
        return hash < 0 ? hash + MOD : hash;
    }
};
template<int MOD> int str_hash<MOD>::P = uniform(256, MOD - 1); // l > |sigma|

