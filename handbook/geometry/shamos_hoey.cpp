// Shamos-hoey algorithm
//
// Description: given a set of segments finds if any two segments intersect
//
// Complexity: O(nlgn)

using S = Segment<ll>;

enum {
	ADD,
	REM
};

bool shamos_hoey(const vector<S>& seg) {
	vector<array<ll, 3> > ev;
	for (int i = 0; i < seg.size(); i++) {
		if(seg[i].q < seg[i].p) swap(seg[i].p, seg[i].q);
		ev.push_back({seg[i].p.x, ADD, i});
		ev.push_back({seg[i].q.x, REM, i});
	}
	sort(ev.begin(), ev.end());
	set<S> s;
	for (const auto &e : ev) {
		S at = seg[e[2]];
		if (e[1] == ADD) {
			auto nxt = s.lower_bound(at);
			if((nxt != s.end() && inter(*nxt, at))
				|| (nxt != s.begin() && inter(*prev(nxt), at))) {
					return 1;
			}
			s.insert(at);
		} else {
			auto nxt = s.upper_bound(at), cur = nxt, prv = --cur;
			if(nxt != s.end() && prv != s.begin() 
				&& inter(*nxt, *(prev(prv)))) return 1;
			s.erase(cur);
		}
	}
	return 0;
}
