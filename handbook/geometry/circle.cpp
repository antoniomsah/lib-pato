// Circle
//
// Complexity: O(1) unless stated

const Point<int> ccw(1,0);

template <class T>
struct Circle {
	using P = Point<T>;
	using C = Circle;

	P c; T r;
	Circle() {}
	Circle(P c, T r) : c(c), r(r) {}

	bool in(C rhs) { return (c-rhs.c).norm2() <= (rhs.r-r)*(rhs.r-r); }
	bool has(P p) { return (c-p).norm2() <= r*r; }

	// returns intersection points between line and circle
	vector<P> intersect(Line<T> l) {
		T h2 = r*r - l.dist2(c);
		if (h2 > -EPS) {
			P p = l.proj(c);
			P h = l.v*sqrt(h2)/l.v.norm();
			if (h.norm() < EPS) return {p};
			return {p+h, p-h};
		}
		return {};
	}

	// returns intersection points between two circles
	vector<P> intersect(C rhs) {
		vector<P> inter;
		C d = (c-rhs.c).norm();
		if(d > r + rhs.r + EPS or d + min(r,rhs.r) + EPS < max(r,rhs.r) ) return inter;
		T x = (d*d - rhs.r*rhs.r + r*r) / (2*d),
		  y = sqrt(r*r - x*x);
		P v = (rhs.c-c)/d;
		inter.push_back(c + v*x - v.rot(ccw)*y);
		if(y>EPS) inter.push_back(c+v*x+v.rot(ccw)*y);
		return inter;
	}
};
