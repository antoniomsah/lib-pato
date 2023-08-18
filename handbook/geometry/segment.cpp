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

	Line<T> getline() { return Line(p,q); }
};

