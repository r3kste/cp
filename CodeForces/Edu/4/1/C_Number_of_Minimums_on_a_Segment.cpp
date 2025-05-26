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
#define sz(a) ((int)(a).size())

#define rep(_, n) \
    int _;        \
    for (_ = 0; _ < n; _++)

#define in(_) cin >> _;
#define in2(_0, _1) cin >> _0 >> _1;
#define in3(_0, _1, _2) cin >> _0 >> _1 >> _2;
#define vin(a)          \
    {                   \
        rep(_, sz(a)) { \
            in(a[_])    \
        }               \
    }
#define vvin(r, c)                \
    {                             \
        rep(__, r) {              \
            rep(_, c) {           \
                in(matrix[__][_]) \
            }                     \
        }                         \
    }
#define br cout << "\n";
#define out(_, __) cout << _ << __;
#define o(_) out(_, " ")
#define vout(__)        \
    for (auto _ : __) { \
        o(_)            \
    }                   \
    br
#define vvout(___)        \
    for (auto __ : ___) { \
        vout(__);         \
    }

#define oyes out("YES", "\n")
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
    vector<int> lazy;
    string update_op;
    string query_op;

    segtree(vector<int> &array, int no_of_elements, const string &update, const string &query) {
        n = no_of_elements;
        arr = array;
        tree.resize(4 * n + 1);
        lazy.resize(4 * n + 1);
        this->update_op = update;
        this->query_op = query;
        build();
    }

    T default_val() {
        // if (query_op == "add" || query_op == "sum") {
        //     return T(0);
        // } else if (query_op == "max") {
        //     return std::numeric_limits<T>::min();
        // } else if (query_op == "min") {
        return mp(INT32_MAX, 0);
        // } else if (query_op == "xor" || query_op == "or") {
        //     return T(0);
        // } else if (query_op == "and") {
        //     return std::numeric_limits<T>::max();
        // } else if (query_op == "gcd") {
        //     return T(0);
        // } else if (query_op == "lcm" || query_op == "mul") {
        //     return T(1);
        // } else if (query_op == "assign") {
        //     return T(0);
        // } else {
        //     return T(0);
        // }
    }

    class Combine {
      public:
        T add(T left_subtree, T right_subtree) {
            return left_subtree + right_subtree;
        }

        T max(T left_subtree, T right_subtree) {
            return left_subtree > right_subtree ? left_subtree : right_subtree;
        }

        T min(T left_subtree, T right_subtree) {
            return left_subtree < right_subtree ? left_subtree : right_subtree;
        }

        T xor_(T left_subtree, T right_subtree) {
            return left_subtree ^ right_subtree;
        }

        T or_(T left_subtree, T right_subtree) {
            return left_subtree | right_subtree;
        }

        T and_(T left_subtree, T right_subtree) {
            return left_subtree & right_subtree;
        }

        T gcd(T left_subtree, T right_subtree) {
            return __gcd(left_subtree, right_subtree);
        }

        T lcm(T left_subtree, T right_subtree) {
            return left_subtree * right_subtree / __gcd(left_subtree, right_subtree);
        }

        T mul(T left_subtree, T right_subtree) {
            return left_subtree * right_subtree;
        }

        T assign([[maybe_unused]] T left_subtree, T right_subtree) {
            return right_subtree;
        }
    };

    auto query_operation(T a, T b) {
        // if (query_op == "add" || query_op == "sum") {
        //     return Combine().add(a, b);
        // } else if (query_op == "max") {
        //     return Combine().max(a, b);
        // } else if (query_op == "min") {
        // } else if (query_op == "xor") {
        //     return Combine().xor_(a, b);
        // } else if (query_op == "or") {
        //     return Combine().or_(a, b);
        // } else if (query_op == "and") {
        //     return Combine().and_(a, b);
        // } else if (query_op == "gcd") {
        //     return Combine().gcd(a, b);
        // } else if (query_op == "lcm") {
        //     return Combine().lcm(a, b);
        // } else if (query_op == "mul") {
        //     return Combine().mul(a, b);
        // } else if (query_op == "assign") {
        //     return Combine().assign(a, b);
        // } else if (query_op == "min_count") {
        if (a.F < b.F) {
            return a;
        } else if (a.F > b.F) {
            return b;
        } else {
            return mp(a.F, a.S + b.S);
        }

        // } else {
        //     return Combine().add(a, b);
        // }
    }

    auto query_operation(int left_vertex, int right_vertex) {
        // if (query_op == "add" || query_op == "sum") {
        //     return Combine().add(tree[left_vertex], tree[right_vertex]);
        // } else if (query_op == "max") {
        //     return Combine().max(tree[left_vertex], tree[right_vertex]);
        // } else if (query_op == "min") {
        //     return Combine().min(tree[left_vertex], tree[right_vertex]);
        // } else if (query_op == "xor") {
        //     return Combine().xor_(tree[left_vertex], tree[right_vertex]);
        // } else if (query_op == "or") {
        //     return Combine().or_(tree[left_vertex], tree[right_vertex]);
        // } else if (query_op == "and") {
        //     return Combine().and_(tree[left_vertex], tree[right_vertex]);
        // } else if (query_op == "gcd") {
        //     return Combine().gcd(tree[left_vertex], tree[right_vertex]);
        // } else if (query_op == "lcm") {
        //     return Combine().lcm(tree[left_vertex], tree[right_vertex]);
        // } else if (query_op == "mul") {
        //     return Combine().mul(tree[left_vertex], tree[right_vertex]);
        // } else if (query_op == "assign") {
        //     return Combine().assign(tree[left_vertex], tree[right_vertex]);
        // } else if (query_op == "min_count") {
        if (tree[left_vertex].F < tree[right_vertex].F) {
            return tree[left_vertex];
        } else if (tree[left_vertex].F > tree[right_vertex].F) {
            return tree[right_vertex];
        } else {
            return mp(tree[left_vertex].F, tree[left_vertex].S + tree[right_vertex].S);
        }

        // } else {
        //     return Combine().add(tree[left_vertex], tree[right_vertex]);
        // }
    }

    void build(int vertex, range borders) {
        if (borders.L == borders.R) {
            if (borders.L <= n) {
                tree[vertex].F = arr[borders.L - 1];
                tree[vertex].S = 1;
            }
        } else {
            int mid = borders.mid();
            build(vertex << 1, {borders.L, mid});
            build(vertex << 1 | 1, {mid + 1, borders.R});
            tree[vertex] = query_operation(vertex << 1, vertex << 1 | 1);
        }
    }

    void build() {
        build(1, {1, n});
    }

    auto point_update_operation(int vertex, T value) {
        // if (update_op == "add" || update_op == "sum") {
        //     return tree[vertex] + value;
        // } else if (update_op == "max") {
        //     return max(tree[vertex], value);
        // } else if (update_op == "min") {
        //     return min(tree[vertex], value);
        // } else if (update_op == "xor") {
        //     return tree[vertex] ^ value;
        // } else if (update_op == "or") {
        //     return tree[vertex] | value;
        // } else if (update_op == "and") {
        //     return tree[vertex] & value;
        // } else if (update_op == "gcd") {
        //     return __gcd(tree[vertex], value);
        // } else if (update_op == "lcm") {
        //     return tree[vertex] * value / __gcd(tree[vertex], value);
        // } else if (update_op == "mul") {
        //     return tree[vertex] * value;
        // } else if (update_op == "assign") {
        return value;
        // } else {
        //     return tree[vertex] + value;
        // }
    }

    void update(int target, T value, int vertex, range borders) {
        if (borders.L == borders.R) {
            tree[vertex] = point_update_operation(vertex, value);
        } else {
            int mid = borders.mid();

            if (target <= mid) {
                update(target, value, vertex << 1, {borders.L, mid});
            } else {
                update(target, value, vertex << 1 | 1, {mid + 1, borders.R});
            }

            tree[vertex] = query_operation(vertex << 1, vertex << 1 | 1);
        }
    }

    void Update(int target, T value) {
        update(target, value, 1, {1, n});
    }

    auto query(range query_range, int vertex, range borders) {
        if (borders.L > query_range.R || borders.R < query_range.L) {
            return default_val();
        } else if (borders.L >= query_range.L && borders.R <= query_range.R) {
            return tree[vertex];
        } else {
            int mid = borders.mid();
            auto left_subtree = query(query_range, vertex << 1, {borders.L, mid});
            auto right_subtree = query(query_range, vertex << 1 | 1, {mid + 1, borders.R});
            return query_operation(left_subtree, right_subtree);
        }
    }

    auto query(range query_range) {
        return query(query_range, 1, {1, n});
    }
};

int solve() {
    fastio int n, m;
    in2(n, m);
    vi a(n);
    vin(a);
    segtree<ii> st(a, n, "assign", "min_count");

    while (m--) {
        int op;
        in(op);

        if (op == 1) {
            int index, value;
            in2(index, value);
            st.Update(index + 1, mp(value, 1));
        } else {
            int l, r;
            in2(l, r);
            auto ans = st.query({l + 1, r});
            out(ans.F, " ");
            out(ans.S, "\n");
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
