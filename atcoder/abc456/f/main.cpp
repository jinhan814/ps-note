#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr i64 inf = i64(1) << 60;

struct node {
	node() : v0(inf), v1(inf), v2(inf), v3(inf), flag(true) {}
	node(int x) : v0(0), v1(inf), v2(inf), v3(x), flag(false) {}
	node operator+ (const node& x) const {
		if (flag) return x;
		if (x.flag) return *this;
		node ret;
		ret.v0 = min({ v0 + x.v2, v1 + x.v0, v1 + x.v2 });
		ret.v1 = min({ v0 + x.v3, v1 + x.v1, v1 + x.v3 });
		ret.v2 = min({ v2 + x.v2, v3 + x.v0, v3 + x.v2 });
		ret.v3 = min({ v2 + x.v3, v3 + x.v1, v3 + x.v3 });
		ret.flag = false;
		return ret;
	}
public:
	i64 v0, v1, v2, v3;
	bool flag;
};

struct segtree {
	segtree(int n) : sz(1 << (__lg(n - 1 | 1) + 1)), tree(sz << 1) {}
	void update(int i, node x) {
		tree[i |= sz] = x;
		while (i >>= 1) tree[i] = tree[i << 1] + tree[i << 1 | 1];
	}
	node query(int l, int r) const {
		node res_l, res_r;
		for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) res_l = res_l + tree[l++];
			if (~r & 1) res_r = tree[r--] + res_r;
		}
		return res_l + res_r;
	}
private:
	int sz;
	vector<node> tree;
};

auto sol = [](int n, int k, auto v) {
	segtree tree(n);
	for (int i = 0; i < n; i++) tree.update(i, node(v[i]));
	i64 ret = inf;
	for (int i = k - 1; i < n; i++) ret = min(ret, tree.query(i - k + 1, i).v3);
	for (int i = k; i < n; i++) ret = min(ret, tree.query(i - k, i).v3);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n, k; cin >> n >> k;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << sol(n, k, v) << '\n';
	}
}