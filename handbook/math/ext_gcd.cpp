// Extended GCD
//
// Let g = gcd(a,b)
// Returns {g,x,y} such that ax+by = g

array<int,3> ext_gcd(int a, int b) {
    if (!a) return {b, 0, 1};
    auto [g, x, y] = ext_gcd(b%a, a);
    return {g, y - b/a*x, x};
}
