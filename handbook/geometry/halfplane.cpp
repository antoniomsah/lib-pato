// Halfplane
//
// Complexity: O(1) unless stated

template <class T>
struct Halfplane {
	using P = Point<T>;
	using H = Halfplane;

	P p,q;
	double ang;

	Halfplane() {}
	Halfplane(P p, P q) : 
		p(p), q(q), ang(atan2((q-p).y, (q-p).x)) {}

	bool operator<(H h) const {
		if(fabsl(ang-h.ang) < EPS) return right(p,q,h.p);
		return ang < h.ang;
	}

	bool operator==(H h) const { return fabsl(ang-h.ang) < EPS; }

	bool out(P r) { return right(p,q,r); }

	friend P intersection(H a, H b) {
		P r(INF,INF);
		inter(Line(a.p,a.q), Line(b.p, b.q), r);
		return r;
	}
};
