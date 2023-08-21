// Xor basis

const int d = 30;
vector<int> basis(d);
auto add = [&](int x){
	for(int i=d-1;i>=0;i--) {
		if((x&(1<<i)) == 0) continue;
		if(!basis[i]){
			basis[i] = x;
			return;
		}
		x ^= basis[i];
	}
};
