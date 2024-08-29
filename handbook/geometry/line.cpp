// Line
//
// Complexity: O(1) unless stated

template <class T>
struct Line {
	using P = Point<T>;
	using L = Line;

	P v; T c;
	Line() {};
	Line(P p, T c) : v(v), c(c) {}
	Line(P p, P q) : v(q - p), c(v ^ p) {}

	T side(P p) { return (v^p)-c; }
	double dist(P p) { return sqrt(dist2(p)); }
	T dist2(P p) { return side(p) * side(p) / v.norm2(); }

	L perp(P p) { return L(p, p + v.perp()); }

	// orthogonal projection and reflection
	P proj(P p) { return p - v.perp() * side(p) / v.norm2(); }
	P refl(P p) { return p - v.perp() * 2 * side(p) / v.norm2(); }

	bool parallel(L l) { return (v ^ l.v) == 0; }

	L translate(P t) { return L(v, c + (v ^ t)); }

	friend bool inter(L l1, L l2, P &q) {
		if (l1.parallel(l2)) return false;
		q = (l2.v*l1.c - l1.v*l2.c)/(l1.v^l2.v);
		return true;
	}

	friend L bisector(L l1, L l2, bool interior) {
		assert((l1.v^l2.v) != 0);
		double sign = (interior? 1: -1);
		return L(l2.v / l2.v.norm() + l1.v / l1.v.norm() * sign,
				 l2.c / l2.v.norm() + l1.c / l1.v.norm() * sign);
	}
};

