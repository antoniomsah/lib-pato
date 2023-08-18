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
};

