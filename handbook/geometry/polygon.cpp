// Polygon structure
//
// Complexity: O(1) unless stated

template <class T>
struct Polygon {
	using P = Point<T>;

	int n;
	vector<P> p;
	Polygon() {}
	Polygon(vector<P> q) : n(q.size()), p(q) {}

	// Positive represents counter-clockwise order. Negative represent clockwise order.
	// Complexity: O(n)
	T orientation() {
		T acum=0;
		for(int i=0; i<n; i++) {
			acum += p[i]^p[(i+1)%n];
		}
		return acum;
	}

	// Complexity: O(n)
	double area() { return double(area2())/2; }
	T area2() { return abs(orientation()); }

	// Return true if point q is inside the polygon. The polygon must be convex and in ccw order.
	// Complexity: O(lgn)
	bool contains(P q) {
		if(right(p[0],p[1],q) or left(p[0],p[n-1],q)) return false;
		int l=1, r=n;
		while(r-l > 1) {
			int m = (l+r)>>1;
			if(!right(p[0],p[m],q)) l=m;
			else r=m;
		}
		if(r == n) return (q-p[0]).norm2() <= (p[n-1]-p[0]).norm2()+EPS;
		return !right(p[l],p[r],q);
	}

	// Returns the squared diameter (uses rotating calipers).
	// Complexity: O(n)
	T diameter(){ 
		T ans=0;
		for(int i=0,j=1; i<n; i++){
			while(((p[(i+1)%n]-p[i])^(p[(j+1)%n]-p[j])) > 0) j = (j+1)%n;
			ans = max(ans, (p[i]-p[j]).norm2());
		}
		return ans;
	}

	// Returns the index of an extreme point 
	// Complexity: O(lgn)
	int extreme(const function<bool(P, P)> &cmp) {
		auto isExtreme = [&](int i, bool& curDir) -> bool {
			curDir = cmp(p[(i + 1) % n], p[i]);
			return !cmp(p[(i + n - 1) % n], p[i]) && !curDir;
		};
		bool lastDir, curDir;
		if(isExtreme(0, lastDir)) return 0;
		int l = 0, r = n; 
		while(l + 1 < r) {
			int m = (l + r) >> 1;
			if(isExtreme(m, curDir)) return m;
			bool relDir = cmp(p[m], p[l]);
			if((!lastDir && curDir) || (lastDir == curDir && relDir == curDir)) {
				l = m;
				lastDir = curDir;
			} else r = m;
		}
		return l;
	}

	// Finds the indices of the two tangents to an external point q
	// Complexity: O(lgn)
	pair<int,int> tangent(P q) {
		auto leftTangent = [&](P r, P s) -> bool {
            return cross(q, r, s) > 0;
        };
        auto rightTangent = [&](P r, P s) -> bool {
            return cross(q, r, s) < 0;
        };
        return {extreme(leftTangent), extreme(rightTangent)};
	}

	// Rotates the polygon points such that
	// p[0] is the lowest leftmost point
	// Complexity: O(n)
	void normalize() {
		rotate(p.begin(), min_element(p.begin(), p.end()), p.end());
	}

	// Minkowsky sum
	// Complexity: O(n)
	Polygon operator+(Polygon& other) {
		vector<P> sum;
        normalize();
        other.normalize();
		ll dir;
        for(int i = 0, j = 0; i < n || j < other.n; i += dir >= 0, j += dir <= 0) {
            sum.pb(p[i % n] + other.p[j % other.n]);
            dir = (p[(i + 1) % n] - p[i % n]) 
                    ^ (other.p[(j + 1) % other.n] - other.p[j % other.n]);
        }
        return Polygon(sum);
	}
};

