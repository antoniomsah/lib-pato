/**
 * Halfplane structure and halfplane intersection algorithm. 
 * Dependencies: line.
 * Complexity: O(1) unless stated.
 **/

struct halfplane {
	point p,q;
	double ang;

	halfplane() {}
	halfplane(point p, point q) : p(p), q(q), ang(atan2((q-p).y, (q-p).x)) {}

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

/**
 * Half-plane intersection algorithm. Either returns an empty vector
 * or a convex polygon that is covered by all half-planes.
 * Dependencies: point and line structures
 * Complexity: O(nlgn)
 **/
vector<point> intersection(vector<halfplane> h) {
	point box[4] = {{-INF,-INF}, {INF,-INF}, {INF,INF}, {-INF,INF}};
	for(int i=0; i<4; i++) {
		h.emplace_back(box[i], box[(i+1)%4]);
	}
	sort(h.begin(), h.end());
	h.resize(unique(h.begin(), h.end()) - h.begin());
	vector<halfplane> dq(h.size());
	int l=0, r=0;
	for(auto hp: h) {
		while(r-l > 1 and hp.out(dq[r-1].intersection(dq[r-2]))) r--;
		while(r-l > 1 and hp.out(dq[l].intersection(dq[l+1]))) l++;
		dq[r++] = hp;
	}
	while(r-l>2 and dq[l].out(dq[r-1].intersection(dq[r-2]))) r--;
	while(r-l>2 and dq[r-1].out(dq[l].intersection(dq[l+1]))) l++;
	if(r-l < 3) return {};
	vector<point> p;
	p.reserve(r-l);
	p.push_back(dq[--r].intersection(dq[l]));
	while(l < r) {
		p.push_back(dq[l].intersection(dq[l+1])), l++;
	}
	return p;
}

