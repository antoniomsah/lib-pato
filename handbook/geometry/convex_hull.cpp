/**
 * Monotone chain algorithm.
 * Border represents the inclusion of collinear points.
 *
 * Complexity: O(nlgn)
 **/

vector<point> convex_hull(vector<point> p, bool border=0){
	if(p.size() == 1) return p;

	int n = p.size(), m=0;
	sort(p.begin(), p.end());

	vector<point> ch;
	for(int i=0; i<n; i++, m++){
		while(m > 1 and sign(area2(ch[m-2], ch[m-1], p[i])) <= -border) {
			ch.pop_back(), m--;
		}
		ch.push_back(p[i]);
	}

	for(int i=n-2, t=m; i>=0; i--, m++){
		while(m > t and sign(area2(ch[m-2], ch[m-1], p[i])) <= -border) {
			ch.pop_back(), m--;
		}
		ch.push_back(p[i]);
	}
	ch.pop_back(); // last element is duplicated

	return ch;
}
