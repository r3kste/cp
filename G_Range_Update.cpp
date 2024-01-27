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
    int L;
    int R;

    [[nodiscard]] int mid() const {
        return L + (R - L) / 2;
    }
};
template<typename T>
struct segtree {
    int n;
    vector<int> arr;
    vector<T> tree;
    vector<T> lazy;
    string update_op;
    string query_op;

    segtree(vector<int> &array, const string &update, const string &query) {
        arr = array;
        n = array.size();
        tree.resize(4 * n + 1);
        lazy.resize(4 * n + 1);
        this->update_op = update;
        this->query_op = query;
        build();
    }

    T default_val() {
        if (query_op == "add" || query_op == "sum") {
            return T(0);
        } else if (query_op == "max") {
            return std::numeric_limits<T>::min();
        } else if (query_op == "min") {
            return std::numeric_limits<T>::max();
        } else if (query_op == "xor" || query_op == "or") {
            return T(0);
        } else if (query_op == "and") {
            return std::numeric_limits<T>::max();
        } else if (query_op == "gcd") {
            return T(0);
        } else if (query_op == "lcm") {
            return T(1);
        } else if (query_op == "mul") {
            return T(1);
        } else if (query_op == "assign") {
            return T(0);
        } else {
            return T(0);
        }
    }
    T operation(string op, T a, T b) {
        if (op == "add" || op == "sum") {
            return a + b;
        } else if (op == "max") {
            return max(a, b);
        } else if (op == "min") {
            return min(a, b);
        } else if (op == "xor") {
            return a ^ b;
        } else if (op == "or") {
            return a | b;
        } else if (op == "and") {
            return a & b;
        } else if (op == "gcd") {
            return __gcd(a, b);
        } else if (op == "lcm") {
            return a * b / __gcd(a, b);
        } else if (op == "mul") {
            return a * b;
        } else if (op == "assign") {
            return b;
        } else {
            return a;
        }
    }

    T build_operation(int left_vertex, int right_vertex) {
        return operation(query_op, tree[left_vertex], tree[right_vertex]);
    }
    void build(int vertex, range borders) {
        if (borders.L == borders.R) {
            if (borders.L <= n) {
                tree[vertex] = arr[borders.L - 1];
            }
        } else {
            int mid = borders.mid();
            build(vertex << 1, {borders.L, mid});
            build(vertex << 1 | 1, {mid + 1, borders.R});
            tree[vertex] = build_operation(vertex << 1, vertex << 1 | 1);
        }
    }
    void build() {
        build(1, {1, n});
    }

    T update_operation(int vertex, T value) {
        return operation(update_op, tree[vertex], value);
    }
    void point_update(int target, T value, int vertex, range borders) {
        if (borders.L == borders.R) {
            tree[vertex] = update_operation(vertex, value);
        } else {
            int mid = borders.mid();

            if (target <= mid) {
                point_update(target, value, vertex << 1, {borders.L, mid});
            } else {
                point_update(target, value, vertex << 1 | 1, {mid + 1, borders.R});
            }

            tree[vertex] = build_operation(vertex << 1, vertex << 1 | 1);
        }
    }
    void update(int target, T value) {
        point_update(target, value, 1, {1, n});
    }
    void range_update(range update_range, T value, int vertex, range borders) {
        if (lazy[vertex] != 0) {
            tree[vertex] += (borders.R - borders.L + 1) * lazy[vertex];

            if (borders.L != borders.R) {
                lazy[vertex << 1] += lazy[vertex];
                lazy[vertex << 1 | 1] += lazy[vertex];
            }

            lazy[vertex] = 0;
        }

        if (borders.L > borders.R || borders.L > update_range.R || borders.R < update_range.L) {
            return;
        }

        if (borders.L >= update_range.L && borders.R <= update_range.R) {
            tree[vertex] += (borders.R - borders.L + 1) * value;

            if (borders.L != borders.R) {
                lazy[vertex << 1] += value;
                lazy[vertex << 1 | 1] += value;
            }

            return;
        }

        int mid = borders.mid();
        range_update(update_range, value, vertex << 1, {borders.L, mid});
        range_update(update_range, value, vertex << 1 | 1, {mid + 1, borders.R});
        tree[vertex] = build_operation(vertex << 1, vertex << 1 | 1);
    }
    void update(range update_range, T value) {
        range_update(update_range, value, 1, {1, n});
    }

    T query_operation(T left_subtree, T right_subtree) {
        return operation(query_op, left_subtree, right_subtree);
    }
    T point_query(int target, int vertex, range borders) {
        if (lazy[vertex] != 0) {
            tree[vertex] += (borders.R - borders.L + 1) * lazy[vertex];

            if (borders.L != borders.R) {
                lazy[vertex << 1] += lazy[vertex];
                lazy[vertex << 1 | 1] += lazy[vertex];
            }

            lazy[vertex] = 0;
        }

        if (borders.L == borders.R) {
            return tree[vertex];
        } else {
            int mid = borders.mid();

            if (target <= mid) {
                return point_query(target, vertex << 1, {borders.L, mid});
            } else {
                return point_query(target, vertex << 1 | 1, {mid + 1, borders.R});
            }
        }
    }
    T query(int target) {
        return point_query(target, 1, {1, n});
    }
    T range_query(range query_range, int vertex, range borders) {
        if (lazy[vertex] != 0) {
            tree[vertex] += (borders.R - borders.L + 1) * lazy[vertex];

            if (borders.L != borders.R) {
                lazy[vertex << 1] += lazy[vertex];
                lazy[vertex << 1 | 1] += lazy[vertex];
            }

            lazy[vertex] = 0;
        }

        if (borders.L > query_range.R || borders.R < query_range.L) {
            return default_val();
        } else if (borders.L >= query_range.L && borders.R <= query_range.R) {
            return tree[vertex];
        } else {
            int mid = borders.mid();
            T left_subtree = range_query(query_range, vertex << 1, {borders.L, mid});
            T right_subtree = range_query(query_range, vertex << 1 | 1, {mid + 1, borders.R});
            return query_operation(left_subtree, right_subtree);
        }
    }
    T query(range query_range) {
        return range_query(query_range, 1, {1, n});
    }
};

int solve() {
    fastio
    int n, m;
    in2(n, m);
    vi a(n);
    vin (a);
    segtree<ll> st(a, "sum", "sum");

    while (m--) {
        int op;
        in (op);

        if (op == 1) {
            int l, r, v;
            in3(l, r, v);
            st.update({l, r}, v);
        } else {
            int k;
            in (k);
            out(st.query(k), "\n");
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
