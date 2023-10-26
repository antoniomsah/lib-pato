// Halfplane
//
// Complexity: O(1) unless stated

template <class T>
struct Halfplane {
	using P = Point<T>;
	using H = Halfplane;

	P p, pq;
	double ang;

	Halfplane() {}
	Halfplane(P p, P q) : p(p), pq(q-p) {
		ang = atan2l(pq.y, pq.x);
	}

	bool operator<(H h) const { return ang < h.ang; }

	bool operator==(H h) const { return fabsl(ang-h.ang) < EPS; }

	bool out(P r) { return (pq^(r-p)) < -EPS; }

	friend P inter(H s, H t) {
		double alpha = ((t.p - s.p)^t.pq) / (s.pq^t.pq);
		return s.p + s.pq*alpha;
	}
};
