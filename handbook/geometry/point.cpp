// Point
//
// Description: 
//		Structure to handle points
//
// Complexity: O(1) unless stated

#warning caution with double precisions

int sign(int x) { return (x>0) - (x<0); }

template <class T>
struct Point {
	T x,y;
	using P = Point;
	Point(T x=0, T y=0) : x(x), y(y) {}

	double norm() { return sqrt(norm2()); }
	T norm2() { return (*this) * (*this); }

	P operator+(P p) { return P(x+p.x, y+p.y); }
	P operator-(P p) { return P(x-p.x, y-p.y); }
	P operator*(T t) { return P(x*t, y*t); }
	P operator/(T t) { return P(x/t, y/t); }

	T operator*(P p) { return x*p.x + y*p.y; }
	T operator^(P p) { return x*p.y - y*p.x; }

	bool operator<(P p) { return tie(x,y) < tie(p.x,p.y); }
	bool operator>(P p) { return tie(x,y) > tie(p.x,p.y); }
	bool operator==(P p) { return tie(x,y) == tie(p.x,p.y); }
	bool operator!=(P p) { return tie(x,y) != tie(p.x,p.y); }

	P rot(P p) { return P((*this)^p, (*this)*p); }
	P rot(double ang) { return rot(P(sin(ang), cos(ang))); }

	double angle() { return atan2(y,x); }
	double angle(P p) { return acos(max(-1.0, min(1.0, (*this)*p/(norm()*p.norm())))); }

	P perp() { return P(-y,x); }
	bool is_perp(P p) { return ((*this) * p) == 0; }

	bool side() { return (y > 0) or (y == 0 and x < 0); }

	friend T cross(P a, P b, P c) { return (b-a)^(c-a); }
	friend bool left(P a, P b, P c) { return area2(a,b,c) > 0; }
	friend bool right(P a, P b, P c) { return area2(a,b,c) < 0; }

	friend ostream& operator<<(ostream& os, P p) {
		return os<<"("<<p.x<<", "<<p.y<<")"; 
	}
};
