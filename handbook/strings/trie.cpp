// Trie data structure
//
// Description: 
// 		Data structure for strings.
//
// Complexity:
//		add: O(|s|)
//		erase: O(|s|)
//		find: O(|s|)

struct trie {
	int sigma, offset;
	vector<int> wrd, cnt;
	vector<vector<int>> to;

	int new_node() {
		wrd.push_back(0);
		cnt.push_back(0);
		to.push_back(vector<int>(sigma));
		return to.size()-1;
	}

	trie(int _sigma=26, int _offset='a') : 
		sigma(_sigma), offset(_offset) {
		new_node();
	}

	// adds s to the trie
	void add(string &s) {
		int i = 0;
		for(char c: s) {
			int &nxt = to[i][c-offset];
			if(!nxt) nxt = new_node();
			cnt[i=nxt]++;
		}
		wrd[i]++;
	}

	// if s is in the trie removes it and returns true,
	// else returns false
	bool erase(string &s) {
		if(!find(s)) return false;
		int i=0;
		for(char c: s) {
			int &nxt = to[i][c-offset];
			cnt[i=nxt]--;
			if(!cnt[nxt]) nxt=0;
		}
		wrd[i]--;
		return true;
	}

	// if s is in the trie returns true,
	// else returns false
	bool find(string &s) {
		int i=0;
		for(char c: s) {
			int &nxt = to[i][c-offset];
			if(!nxt) return false;
			i = nxt;
		}
		return (wrd[i] > 0);
	}
};
