#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef pair<int, int> ii;

typedef vector<int> vi;
typedef vector<char> vc;
typedef vector<bool> vb;
typedef vector<ll> vll;
typedef vector<vi> vvi;

#define MOD (ll)(1e9 + 7)
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);

#define F first
#define S second
#define mp make_pair
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define sz(a) ((int) (a).size())

#define rep(_, n) int _; for(_ = 0; _ < n; _++)

#define in(_) cin >> _;
#define in2(_0, _1) cin >> _0 >> _1;
#define in3(_0, _1, _2) cin >> _0 >> _1 >> _2;
#define vin(a) { rep (_, sz (a)) { in (a[_]) }}
#define vvin(r, c) { rep(__,r) { rep(_,c) { in (matrix[__][_]) } } }
#define br cout << "\n";
#define out(_, __) cout << _ << __;
#define o(_) out(_, " ")
#define vout(__) for (auto _ : __) { o (_) } br
#define vvout(___)  for (auto __ : ___) { vout (__); }

#define oyes out("YES","\n")
#define ono out("NO", "\n")

bool comp(ii a, ii b) {
    if (a.F == b.F) {
        return a.S > b.S;
    } else {
        return a.F < b.F;
    }
}

template<typename T>
struct segtree {
    struct range {
        int L;
        int R;

        [[nodiscard]] int mid() const {
            return L + (R - L) / 2;
        }
    };

    static const T DEFAULT_VAL = 0;
    static const T DEFAULT_LAZY = 0;
    struct node {
        T val;
        T lazy;

        node() {
            val = DEFAULT_VAL;
            lazy = DEFAULT_LAZY;
        }
    };

    int n;
    vector<int> arr;
    vector<node> tree;

    explicit segtree(vector<int> &array) {
        arr = array;
        n = (int) array.size();
        tree.resize(4 * n + 1);
        build();
    }

    T default_val() {
        /**/
        return 0;
        /**/
    }

    T build_operation(int left_vertex, int right_vertex);
    T update_operation(int vertex, T value);

    void build(int vertex, range borders) {
        if (borders.L == borders.R) {
            if (borders.L <= n) {
                tree[vertex].val = arr[borders.L - 1];
            }
        } else {
            int mid = borders.mid();
            build(vertex << 1, {borders.L, mid});
            build(vertex << 1 | 1, {mid + 1, borders.R});
            tree[vertex].val = build_operation(vertex << 1, vertex << 1 | 1);
        }
    }

    void point_update(int target, T value, int vertex, range borders) {
        if (borders.L == borders.R) {
            tree[vertex].val = update_operation(vertex, value);

            if (tree[vertex].val == 0) {
                o(borders.L);
            }
        } else {
            int mid = borders.mid();

            // if (target <= mid) {
            //     point_update(target, value, vertex << 1, {borders.L, mid});
            // } else {
            //     point_update(target, value, vertex << 1 | 1, {mid + 1, borders.R});
            // }

            if (tree[vertex << 1].val == tree[vertex].val) {
                point_update(target, value, vertex << 1, {borders.L, mid});
            } else {
                point_update(target, value, vertex << 1 | 1, {mid + 1, borders.R});
            }

            tree[vertex].val = build_operation(vertex << 1, vertex << 1 | 1);
        }
    }

    void build() {
        build(1, {1, n});
    }

    void update(int target, T value) {
        point_update(target, value, 1, {1, n});
    }

    // void update(range update_range, T value) {
    //     range_update(update_range, value, 1, {1, n});
    // }

    // T query(int target) {
    //     return point_query(target, 1, {1, n});
    // }

    // T query(range query_range) {
    //     return range_query(query_range, 1, {1, n});
    // }
};

template<typename T>
T segtree<T>::build_operation(int left_vertex, int right_vertex) {
    /* How to combine two nodes into one parent node */
    return max(tree[left_vertex].val, tree[right_vertex].val);
    /**/
}

template<typename T>
T segtree<T>::update_operation(int vertex, T value) {
    /* How to update the value in tree[vertex] */
    return max(tree[vertex].val - value, 0);
    /**/
}

int solve() {
    fastio
    int n, k;
    in2(n, k);
    vi a(n);

    for (int i = 0; i < n; i++) {
        int temp;
        in(temp);
        temp %= k;

        if (temp == 0) {
            temp = k;
        }

        a[i] = temp;
    }

    segtree<int> st(a);

    while (st.tree[1].val != 0) {
        st.update(1, k);
    }

    br;
    return 0;
}

int main() {
    fastio;
    int t = 1;
    in (t);

    while (t--) {
        solve();
    }
}
