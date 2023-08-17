// Halfplane structure
//
// Dependencies: point and line
//
// Complexity: O(1) unless stated

struct halfplane {
	point p,q;
	double ang;

	halfplane() {}
	halfplane(point p, point q) : 
		p(p), q(q), ang(atan2((q-p).y, (q-p).x)) {}

	bool operator<(const halfplane& rhs) const {
		if(fabsl(ang-rhs.ang) < EPS) return right(p,q,rhs.p);
		return ang < rhs.ang;
	}

	bool operator==(const halfplane& rhs) const { return fabsl(ang-rhs.ang) < EPS; }

	bool out(point r) { return right(p,q,r); }

	point intersection(const halfplane& rhs) const {
		point r(INF,INF);
		inter(line(p,q), line(rhs.p,rhs.q), r);
		return r;
	}
};
