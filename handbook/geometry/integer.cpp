// Basic geometry structures using integers
//
// Complexity: O(1) unless stated

using coord = long long;
const double EPS = 1e-8;

int sign(coord x) { return (x > 0) - (x < 0); }

struct point {
	coord x,y;
	
	point() {}
	point(coord x, coord y) : x(x), y(y) {}
	
	// returns the norm of a vector
	double norm() { return sqrt(norm2()); }
	coord norm2() { return (*this)*(*this); } // squared norm

	point operator+(const point& rhs) const { return {x+rhs.x, y+rhs.y}; }
	point operator-(const point& rhs) const { return {x-rhs.x, y-rhs.y}; }
	point operator*(const coord t) const { return {x*t, y*t}; }
	point operator/(const coord t) const { return {x/t, y/t}; }

	// dot product
	coord operator*(const point& rhs) const { return x*rhs.x + y*rhs.y; }

	// cross product
	coord operator^(const point& rhs) const { return x*rhs.y - y*rhs.x; }

	bool operator<(const point& rhs) const { return make_pair(x,y) < make_pair(rhs.x,rhs.y); }
	bool operator>(const point& rhs) const { return rhs < *this; }
	bool operator==(const point& rhs) const { return make_pair(x,y) == make_pair(rhs.x, rhs.y); }
	bool operator!=(const point& rhs) const { return !(*this == rhs); }

	// counter-clockwise rotation
	// caution: most times will return a double hence not reliable for integers
	point rot(const point& rhs) { return point(*this ^ rhs, *this * rhs); }
	point rot(double ang) { return rot(point(sin(ang), cos(ang))); }
	double angle(point rhs) {
		return acos(max(-1.0, min(1.0, *this * rhs / (norm() * rhs.norm()))));
	}

	point perp() { return {-y,x}; }
	bool is_perp(const point& rhs) const { return (*this * rhs) == 0; }

	bool side() { return y > 0 or (y == 0 and x < 0); }
};

// returns two times the area of the triangle
coord area2(point a, point b, point c) {
	return (b-a)^(c-a);
}

bool left(point a, point b, point c) {
	return area2(a,b,c) > 0;
}

bool right(point a, point b, point c) {
	return area2(a,b,c) < 0;
}

// sorts the point array based on angle
void polarsort(vector<point> &v) {
	sort(v.begin(), v.end(), [](point a, point b) {
		return make_tuple(a.side(),0) < make_tuple(b.side(), a^b);
	});
}

// for point debugging
ostream& operator<<(ostream& os, point p){ return os<<"("<<p.x<<","<<p.y<<")"; }

struct line {
	point v; // v = q-p
	coord c;

	line() {}
	line(point v, coord c) : v(v), c(c) {}
	line(point p, point q) : v(q-p), c(v^p) {}

	// +1: above, -1: below, =0: colinear
	coord side(point p) { return (v^p)-c; }
	coord dist(point p) { return sqrt(dist2(p)); }
	coord dist2(point p) { return side(p)*side(p)/v.norm2(); }

	line perp(point p) { return {p, p+v.perp()}; }
	point proj(point p) { return p - v.perp()*side(p)/v.norm2(); }
	bool parallel(const line& rhs) const { return (v^rhs.v) == 0; }
};

bool inter(const line l1, const line l2, point &q) {
	if(l1.parallel(l2)) return false;
	q = (l2.v*l1.c - l1.v*l2.c)/(l1.v^l2.v);
	return true;
}

struct segment {
	point p,q;

	segment(point p, point q) : p(p), q(q) {};

	bool inDisk(point r) { return (p-r)*(q-r) <= 0; }
	bool has(point r) { return area2(p,q,r) == 0 and inDisk(r); }

	coord side(point r) { return sign((r-p)^(q-p)); }
	coord len() { return (q-p).norm(); }
	coord len2() { return (q-p).norm2(); }

	line getline() { return line(p,q); }
};

point ccw90(1,0);

struct circle {
	point c; coord r;
	circle() {}
	circle(point c, coord r) : c(c), r(r) {}

	bool in(circle rhs) { return (c-rhs.c).norm2() <= (rhs.r-r)*(rhs.r-r); }
	bool has(point p) { return (c-p).norm2() <= r*r; }

	// returns intersection points between line and circle
	vector<point> operator^(line l) {
		coord d = l.dist(c);
		if(sign(d-r) > 0) return {};
		point proj = l.proj(c);
		if(sign(d-r) == 0) return {proj}; 
		point aux = (l.v.perp()/l.v.norm()) * sqrt(r*r-d*d);
		return {proj+aux, proj-aux};
	}

	// returns intersection points between two circles
	vector<point> operator^(circle rhs) {
		vector<point> inter;
		coord d = (c-rhs.c).norm();
		if(d > r + rhs.r + EPS or d + min(r,rhs.r) + EPS < max(r,rhs.r) ) return inter;
		coord x = (d*d - rhs.r*rhs.r + r*r) / (2*d),
		  y = sqrt(r*r - x*x);
		point v = (rhs.c-c)/d;
		inter.push_back(c + v*x - v.rot(ccw90)*y);
		if(y>EPS) inter.push_back(c+v*x+v.rot(ccw90)*y);
		return inter;
	}
};

point circumcenter(point a, point b, point c){
	b = b-a; c = c-a;
	assert((b^c) != 0); // a,b,c alligned = no circumcircle
	return a + (b*c.norm2()-c*b.norm2()).perp()/((b^c)*2);
}
