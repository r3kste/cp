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
struct range {
    ll L;
    ll R;

    [[nodiscard]] ll mid() const {
        return L + (R - L) / 2;
    }
};

template<typename T>
struct node {
    ll val;
    T lazy;
    const T DEFAULT_VAL = LLONG_MIN;
    const T DEFAULT_LAZY = 0;

    node() {
        val = DEFAULT_VAL;
        lazy = DEFAULT_LAZY;
    }
};

template<typename T>
struct segtree {
    int n;
    vector<ll> arr;
    vector<node<ll >> tree;

    explicit segtree(vector<ll>& array) {
        arr = array;
        n = (ll) array.size();
        tree.resize(4 * n + 1);
        build();
    }

    T default_val() {
        /**/
        return LLONG_MIN;
        /**/
    }

    T build_operation(int left_vertex, int right_vertex);

    T update_operation(int vertex, T value);

    T query_operation(T left_subtree, T right_subtree);

    T lazy_operation(T value, int vertex, range borders);

    void build(int vertex, range borders) {
        if (borders.L == borders.R) {
            if (borders.L <= n) {
                tree[vertex].val = arr[borders.L - 1];
            }
        } else {
            int mid = borders.mid();
            build(vertex << 1, {borders.L, mid});
            build(vertex << 1 | 1, {mid + 1, borders.R});
            tree[vertex].val = max(tree[vertex << 1].val, tree[vertex << 1 | 1].val);
        }
    }

    void point_update(int target, T value, int vertex, range borders) {
        if (borders.L == borders.R) {
            tree[vertex].val = value;
        } else {
            int mid = borders.mid();

            if (target <= mid) {
                point_update(target, value, vertex << 1, {borders.L, mid});
            } else {
                point_update(target, value, vertex << 1 | 1, {mid + 1, borders.R});
            }

            tree[vertex].val = max(tree[vertex << 1].val, tree[vertex << 1 | 1].val);
        }
    }

    T point_query(int target, int vertex, range borders) {
        if (borders.L == borders.R) {
            return tree[vertex].val;
        } else {
            int mid = borders.mid();

            if (target <= mid) {
                return point_query(target, vertex << 1, {borders.L, mid});
            } else {
                return point_query(target, vertex << 1 | 1, {mid + 1, borders.R});
            }
        }
    }

    T range_query(range query_range, int vertex, range borders) {
        if (borders.L > query_range.R || borders.R < query_range.L) {
            return default_val();
        } else if (borders.L >= query_range.L && borders.R <= query_range.R) {
            return tree[vertex].val;
        } else {
            int mid = borders.mid();
            T left_subtree = range_query(query_range, vertex << 1, {borders.L, mid});
            T right_subtree = range_query(query_range, vertex << 1 | 1, {mid + 1, borders.R});
            return max(left_subtree, right_subtree);
        }
    }

    void build() {
        build(1, {1, n});
    }

    void update(int target, T value) {
        point_update(target, value, 1, {1, n});
    }

    T query(int target) {
        return point_query(target, 1, {1, n});
    }

    T query(range query_range) {
        return range_query(query_range, 1, {1, n});
    }

    T range_query2(range query_range, int value, int vertex, range borders) {
        if (borders.L > query_range.R || borders.R < query_range.L) {
            return default_val();
        } else if (borders.L == borders.R) {
            if (tree[vertex].val >= value) {
                return borders.L;
            } else {
                return n + 1;
            }
        } else {
            ll mid = borders.mid();
            T m = n + 1;

            if (tree[vertex << 1].val >= value) {
                if (query_range.L <= mid && borders.L <= query_range.R) {
                    m = min(m, range_query2(query_range, value, vertex << 1, {borders.L, mid}));

                    if (m != n + 1) {
                        return m;
                    }
                }
            }

            if (tree[vertex << 1 | 1].val >= value) {
                if (query_range.L <= borders.R && mid + 1 <= query_range.R) {
                    m = min(m, range_query2(query_range, value, vertex << 1 | 1, {mid + 1, borders.R}));
                }
            }

            return m;
        }
    }
};

int solve() {
    fastio
    int n, q;
    in2(n, q);
    vll a(n);
    vin (a);
    segtree<ll> st(a);
    ll vertex, value;

    while(q--) {
        int op;
        in(op);

        switch (op) {
        case 1:
            in2(vertex, value);
            st.update(vertex, value);
            break;

        case 2:
            ll l, r;
            in2(l, r);
            out(st.query({l, r}), "\n");
            break;

        case 3:
            ll v, x;
            in(v);
            in(x);
            out(st.range_query2({v, n}, x, 1, {1, n}), "\n");
            break;

        default:
            break;
        }
    }

    return 0;
}

int main() {
    fastio;
    int t = 1;
    // in (t);

    while (t--) {
        solve();
    }
}
