// Segment
//
// Complexity: O(1) unless stated

template <class T>
struct Segment {
	using P = Point<T>;
	using S = Segment;

	P p,q;
	Segment() {}
	Segment(P p, P q) : p(p), q(q) {}

	bool inDisk(P r) { return (p-r)*(q-r) <= 0; }
	bool has(P r) { return cross(p,q,r) == 0 and inDisk(r); }

	T side(P r) { return sign((r-p)^(q-p)); }
	double len() { return (q-p).norm(); }
	T len2() { return (q-p).norm2(); }

	// for Shamos-Hoey
#warning caution in the case p == s.q (ex. checking if a polygon is simple)
	bool operator<(S s) {
		if (p == s.p) return cross(p, q, s.q) > 0;
		if (p.x != q.x and (s.p.x == s.q.x or p.x < s.p.x))
			return cross(p, q, s.p) > 0;
		return cross(p, s.q, s.p) > 0;
	}

	// checks if two segments intersect
	friend bool inter(S a, S b) {
		if (a.has(b.p) or a.has(b.q) or b.has(a.p) or b.has(a.q)) {
			return true;
		}
		P out;
		return properInter(a, b, out);
	}

	friend bool properInter(S s1, S s2, P &out) {
		P a = s1.p, b = s1.q, c = s2.p, d = s2.q;

		double oa = cross(c, d, a),
			   ob = cross(c, d, b),
			   oc = cross(a, b, c),
			   od = cross(a, b, d);

		if (oa*ob < 0 and oc*od < 0) {
			out = (a*ob - b*oa) / (ob-oa);
			return true;
		}

		return false;
	}

	Line<T> getLine() { return Line(p,q); }
};

