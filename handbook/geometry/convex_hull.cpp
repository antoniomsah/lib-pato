// Convex hull
//
// Description: 
// 		Monotone chain algorihtm.
// 		Border represents the inclusion of collinear points
//
// Complexity: O(nlgn)

template <typename T>
vector<T> convex_hull(vector<T> p, bool border=0){
	sort(p.begin(), p.end());
	p.erase(unique(p.begin(), p.end()), p.end()); // removes duplicated points

	if(p.size() == 1) return p;
	int n = p.size(), m=0;
	vector<T> ch;
	for(int i=0; i<n; i++, m++){
		while(m > 1 and sign(cross(ch[m-2], ch[m-1], p[i])) <= -border) {
			ch.pop_back(), m--;
		}
		ch.push_back(p[i]);
	}

	for(int i=n-2, t=m; i>=0; i--, m++){
		while(m > t and sign(cross(ch[m-2], ch[m-1], p[i])) <= -border) {
			ch.pop_back(), m--;
		}
		ch.push_back(p[i]);
	}
	ch.pop_back(); // last element is duplicated

	return ch;
}
