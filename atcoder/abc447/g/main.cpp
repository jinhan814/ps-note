#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct node {
	node() {}
	node(i64 x, int a, int b) {
		if (a > b) swap(a, b);
		v.push_back(pair(x, pair(a, b)));
	}
	node operator+ (const node& x) const {
		auto c = v;
		for (auto [x, val] : x.v) {
			bool flag = false;
			for (int i = 0; i < c.size(); i++) {
				if (c[i].second.first != val.first) continue;
				if (c[i].second.second != val.second) continue;
				c[i].first = max(c[i].first, x);
				flag = true;
				break;
			}
			if (!flag) c.push_back(pair(x, val));
		}
		sort(c.begin(), c.end(), greater{});
		node ret;
		int mask = 0;
		for (auto [x, val] : c) {
			if (ret.v.empty()) {
				ret.v.push_back(pair(x, val));
			}
			else {
				bool f1 = ret.v[0].second.first != val.first && ret.v[0].second.first != val.second;
				bool f2 = ret.v[0].second.second != val.first && ret.v[0].second.second != val.second;
				bool flag = false;
				if (~mask & 1 && f1) mask |= 1, flag = true;
				if (~mask & 2 && f2) mask |= 2, flag = true;
				if (!flag) continue;
				ret.v.push_back(pair(x, val));
				if (mask == 3) break;
			}
		}
		return ret;
	}
	i64 get(int i) const {
		for (auto [x, val] : v) {
			if (val.first == i) continue;
			if (val.second == i) continue;
			return x;
		}
		return -1;
	}
private:
	vector<pair<i64, pair<int, int>>> v;
};

struct segtree {
	segtree(int n) : sz(1 << (__lg(n - 1 | 1) + 1)), tree(sz << 1) {}
	void update(int i, node x) {
		--i |= sz;
		do tree[i] = tree[i] + x; while (i >>= 1);
	}
	node query(int l, int r) const {
		node ret;
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret = ret + tree[l++];
			if (~r & 1) ret = ret + tree[r--];
		}
		return ret;
	}
private:
	int sz;
	vector<node> tree;
};

auto sol = [](int n, auto a, auto b) {
	vector l(n, vector(0, pair(0, 0)));
	vector r(n, vector(0, pair(0, 0)));
	for (int i = 0; i < n; i++) {
		if (i - 1 >= 0) l[i] = l[i - 1];
		bool flag = false;
		for (auto& [x, val] : l[i]) {
			if (val != a[i]) continue;
			x = max(x, b[i]);
			flag = true;
			break;
		}
		if (!flag) {
			l[i].push_back(pair(b[i], a[i]));
			sort(l[i].begin(), l[i].end(), greater{});
			if (l[i].size() > 4) l[i].pop_back();
		}
	}
	for (int i = n - 1; i >= 0; i--) {
		if (i + 1 < n) r[i] = r[i + 1];
		bool flag = false;
		for (auto& [x, val] : r[i]) {
			if (val != a[i]) continue;
			x = max(x, b[i]);
			flag = true;
			break;
		}
		if (!flag) {
			r[i].push_back(pair(b[i], a[i]));
			sort(r[i].begin(), r[i].end(), greater{});
			if (r[i].size() > 4) r[i].pop_back();
		}
	}
	segtree tree(n);
	i64 ret = -1;
	for (int i = 2; i <= n - 3; i++) {
		for (int p1 = 0; p1 < r[i + 1].size(); p1++) {
			if (r[i + 1][p1].second == a[i]) continue;
			for (int p2 = p1 + 1; p2 < r[i + 1].size(); p2++) {
				if (r[i + 1][p2].second == a[i]) continue;
				int v1 = a[i];
				int v2 = r[i + 1][p1].second;
				int v3 = r[i + 1][p2].second;
				if (v1 > v2) swap(v1, v2);
				if (v1 > v3) swap(v1, v3);
				if (v2 > v3) swap(v2, v3);
				i64 val = i64(b[i]) + r[i + 1][p1].first + r[i + 1][p2].first;
				if (v1 - 1 >= 1) {
					i64 res = tree.query(1, v1 - 1).get(a[i]);
					if (res != -1) ret = max(ret, res + val);
				}
				if (v1 + 1 <= v2 - 1) {
					i64 res = tree.query(v1 + 1, v2 - 1).get(a[i]);
					if (res != -1) ret = max(ret, res + val);
				}
				if (v2 + 1 <= v3 - 1) {
					i64 res = tree.query(v2 + 1, v3 - 1).get(a[i]);
					if (res != -1) ret = max(ret, res + val);
				}
				if (v3 + 1 <= n) {
					i64 res = tree.query(v3 + 1, n).get(a[i]);
					if (res != -1) ret = max(ret, res + val);
				}
			}
		}
		for (int p1 = 0; p1 < l[i - 1].size(); p1++) {
			if (l[i - 1][p1].second == a[i]) continue;
			for (int p2 = p1 + 1; p2 < l[i - 1].size(); p2++) {
				if (l[i - 1][p2].second == a[i]) continue;
				i64 val = i64(b[i]) + l[i - 1][p1].first + l[i - 1][p2].first;
				tree.update(a[i], node(val, l[i - 1][p1].second, l[i - 1][p2].second));
			}
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector a(n, 0), b(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
	cout << sol(n, a, b) << '\n';
}