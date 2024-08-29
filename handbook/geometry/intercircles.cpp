// Circle intersection area algorithm
//
// Description: finds the area covered by at least k circles.
//
// Complexity: O(n^2 lgn) with high constant.

using P = Point<long long>;
using C = Circle<long long>;

bool cmp(P a, P b, P o) {
	a = a - o, b = b - o;
	return make_tuple(-a.side(), 0) < make_tuple(-b.side(), a^b);
}

vector<double> intercircles(vector<C> &c) {
	// area covered by at least k circles
	vector<double> cover(c.size()+1); 
	for (int i = 0; i < c.size(); i++) {
		int k = 1;
		vector<pair<P,int>> p = {{c[i].c + P(1,0)*c[i].r, 0}, {c[i].c - P(1,0)*c[i].r, 0}};

		for (int j = 0; j < c.size(); j++) {
			bool b0 = c[i].in(c[j]), b1 = c[j].in(c[i]);
			if(b0 and (!b1 or i<j)) k++;
			else if (!b0 and !b1) {
				auto v = c[i].intersect(c[j]);
				if (v.size() == 2) {
					p.push_back({v[0], 1}); p.push_back({v[1], -1});
					if (cmp(v[1], v[0], c[i].c)) k++;
				}
			}
		}

		P o = c[i].c;
		sort(p.begin(), p.end(),[&o](auto a, auto b) { 
			return cmp(a.first,b.first,o); 
		});
	
		for (int j = 0; j < p.size(); j++) {
			P a = p[j? j-1: p.size()-1].first, // (j-1+p.size())%p.size()
				  b = p[j].first;
			double ang = (a - c[i].c).angle(b-c[i].c);
			cover[k] += (a.x - b.x) * (a.y + b.y) / 2.0 + c[i].r * c[i].r * (ang - sin(ang)) / 2.0;
			k += p[j].second;
		}
	}
	return cover;
}
