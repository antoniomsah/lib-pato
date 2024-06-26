// MOs algorithm
//
// Description:
// 		Answers queries offline with sqrt decomposition
//
// Complexity:
// 		exec: O(nsqrt(n)(O(remove)+O(add)))

const int SZ = 230;

struct Query {
    int l, r, idx;
    Query () {}
    Query (int _l, int _r, int _idx) : l(_l), r(_r), idx(_idx) {}
    bool operator < (const Query &o) const {
        return {l / SZ, r} < {o.l / SZ, o.r};
    }
};

template <typename T>
struct MO {
    int sum;
    MO(vector<T> &v) : sum(0), v(v), cnt(MAXN), C(MAXN) {}

    void exec(vector<Query> &queries, vector<T> &answers) {
        answers.resize(queries.size());
        sort(queries.begin(), queries.end());

        int cur_l = 0;
        int cur_r = -1;

        for (Query q : queries) {
            while (cur_l > q.l) {
                cur_l--;
                add(cur_l);
            }
            while (cur_r < q.r) {
                cur_r++;
                add(cur_r);
            }
            while (cur_l < q.l) {
                remove(cur_l);
                cur_l++;
            }
            while (cur_r > q.r) {
                remove(cur_r);
                cur_r--;
            }
            answers[q.idx] = get_answer(cur_l, cur_r);
        }
    }

    void add(int i) {
        sum += v[i];
    }

    void remove(int i) {
        sum -= v[i];
    }

    T get_answer(int l, int r) {
        return sum;
    }
};
