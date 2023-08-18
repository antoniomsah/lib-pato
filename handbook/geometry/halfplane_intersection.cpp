// Halfplane intersection algorithm
//
// Description:
// 		Finds a convex polygon that is covered by all halfplanes.
// 		If does not exist, then returns an empty vector.
//
// Complexity: O(nlgn)

vector<P> intersection(vector<H> h) {
	P box[4] = {{-INF,-INF}, {INF,-INF}, {INF,INF}, {-INF,INF}};
	for(int i=0; i<4; i++) {
		h.emplace_back(box[i], box[(i+1)%4]);
	}
	sort(h.begin(), h.end());
	h.resize(unique(h.begin(), h.end()) - h.begin());
	vector<H> dq(h.size());
	int l=0, r=0;
	for(auto hp: h) {
		while(r-l > 1 and hp.out(intersection(dq[r-1], dq[r-2]))) r--;
		while(r-l > 1 and hp.out(intersection(dq[l], dq[l+1]))) l++;
		dq[r++] = hp;
	}
	while(r-l>2 and dq[l].out(intersection(dq[r-1], dq[r-2]))) r--;
	while(r-l>2 and dq[r-1].out(intersection(dq[l], dq[l+1]))) l++;
	if(r-l < 3) return {};
	vector<P> p;
	p.reserve(r-l);
	p.push_back(intersection(dq[--r], dq[l]));
	while(l < r) {
		p.push_back(intersection(dq[l], dq[l+1])), l++;
	}
	return p;
}

