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
	vector<P> operator^(Line<T> l) {
		T d = l.dist(c);
		if(sign(d-r) > 0) return {};
		P proj = l.proj(c);
		if(sign(d-r) == 0) return {proj}; 
		P aux = (l.v.perp()/l.v.norm()) * sqrt(r*r-d*d);
		return {proj+aux, proj-aux};
	}

	// returns intersection points between two circles
	vector<P> operator^(C rhs) {
		vector<P> inter;
		C d = (c-rhs.c).norm();
		if(d > r + rhs.r + EPS or d + min(r,rhs.r) + EPS < max(r,rhs.r) ) return inter;
		T x = (d*d - rhs.r*rhs.r + r*r) / (2*d),
		  y = sqrt(r*r - x*x);
		P v = (rhs.c-c)/d;
		inter.push_back(c + v*x - v.rot(ccw90)*y);
		if(y>EPS) inter.push_back(c+v*x+v.rot(ccw90)*y);
		return inter;
	}
};
