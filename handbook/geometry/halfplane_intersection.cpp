// Halfplane intersection algorithm
//
// Description:
// 		Finds a convex polygon that is covered by all halfplanes.
// 		If does not exist, then returns an empty vector.
//
// Dependencies: halfplane
//
// Complexity: O(nlgn)

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

