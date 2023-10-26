// Halfplane intersection algorithm
//
// Description: Finds a convex polygon that is covered by all halfplanes. 
// If does not exist, then returns an empty vector.
//
// Complexity: O(nlgn)

vector<P> hp_intersect(vector<H>& h) {
	P box[4] = {
		P(INF, INF),
		P(-INF, INF),
		P(-INF, -INF),
		P(INF, -INF)
	};

	for (int i = 0; i < 4; i++) {
		H aux(box[i], box[(i+1)%4]);
		h.push_back(aux);
	}

	sort(all(h));
	deque<H> dq;
	int len = 0;
	for (int i = 0; i < h.size(); i++) {
		while (len > 1 and h[i].out(inter(dq[len-1], dq[len-2]))) {
			dq.pop_back(), --len;
		}

		while (len > 1 and h[i].out(inter(dq[0], dq[1]))) {
			dq.pop_front(), --len;
		}

		if (len > 0 and fabsl(h[i].pq^dq[len-1].pq) < EPS) {
			if (h[i].pq*dq[len-1].pq < 0.0) return vector<P>();

			if (h[i].out(dq[len-1].p)) {
				dq.pop_back(), --len;
			}
			else continue;
		}

		dq.push_back(h[i]);
		++len;
	}

	while (len > 2 and dq[0].out(inter(dq[len-1], dq[len-2]))) {
		dq.pop_back(), --len;
	}

	while (len > 2 and dq[len-1].out(inter(dq[0], dq[1]))) {
		dq.pop_front(), --len;
	}

	if (len < 3) return vector<P>();

	vector<P> ret(len);
	for (int i = 0; i+1 < len; i++) {
		ret[i] = inter(dq[i], dq[i+1]);
	}
	ret.back() = inter(dq[len-1], dq[0]);
	return ret;
}
