
template <class T>
struct Line {
	using P = Point<T>;
	using L = Line;

	P v; T c;
	Line() {};
	Line(P p, T c) : v(v), c(c) {}
	Line(P p, P q) : v(q-p), c(v^p) {}

	T side(P p) { return (v^p)-c; }
	double dist(P p)  { return sqrt(dist2(p)); }
	T dist2(P p) { return side(p)*side(p)/v.norm2(); }

	L perp(P p) { return P(p, p+v.perp()); }
	P proj(P p) { return p - v.perp()*side(p)/v.norm2(); }
	bool parallel(L l) { return (v^L.v) == 0; }

	friend bool inter(L l1, L l2, P &q) {
		if(l1.parallel(l2)) return false;
		q = (l2.v*l1.c - l1.v*l2.c)/(l1.v^l2.v);
		return true;
	}
};

