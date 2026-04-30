#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct fenwick {
	fenwick(int n) : sz(n), tree(n + 1) {}
	void update(int i, i64 x) {
		for (; i <= sz; i += i & -i) tree[i] += x;
	}
	i64 query(int i) const {
		i64 ret = 0;
		for (; i; i -= i & -i) ret += tree[i];
		return ret;
	}
	i64 query(int l, int r) const {
		return query(r) - query(l - 1);
	}
private:
	int sz;
	vector<i64> tree;
};

auto sol = [](int n, auto v, auto qs) {
	vector dp(n + 1, fenwick(n));
	i64 acc = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			i64 val = 0;
			if (i > 1) val = max(val, dp[i - 1].query(j));
			if (j > 1) val = max(val, dp[i].query(j - 1));
			val += v[i][j];
			acc += val;
			if (j > 1) val -= dp[i].query(j - 1);
			dp[i].update(j, val);
		}
	}
	auto update = [&](int i, int j, int x) {
		v[i][j] += x;
		int l = j, r = j;
		while (r + 1 <= n) {
			i64 val = dp[i].query(r) + x;
			if (i > 1) val = max(val, dp[i - 1].query(r + 1));
			val += v[i][r + 1];
			if (dp[i].query(r + 1) != val) r++;
			else break;
		}
		dp[i].update(l, x);
		dp[i].update(r + 1, -x);
		acc += (r - l + 1) * x;
		for (int iter = i + 1; iter <= n; iter++) {
			int nl = l;
			while (nl <= r) {
				i64 val = dp[iter - 1].query(nl);
				if (nl > 1) val = max(val, dp[iter].query(nl - 1));
				val += v[iter][nl];
				if (dp[iter].query(nl) == val) nl++;
				else break;
			}
			if (nl > r) break;
			int nr = r;
			while (nr + 1 <= n) {
				i64 val = dp[iter].query(nr) + x;
				val = max(val, dp[iter - 1].query(nr + 1));
				val += v[iter][nr + 1];
				if (dp[iter].query(nr + 1) != val) nr++;
				else break;
			}
			l = nl;
			r = nr;
			dp[iter].update(l, x);
			dp[iter].update(r + 1, -x);
			acc += (r - l + 1) * x;
		}
	};
	vector ret(n + 1, i64(0));
	ret[0] = acc;
	for (int i = 1; i <= n; i++) {
		auto [a, b, x] = qs[i];
		update(a, b, x);
		ret[i] = acc;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, vector(n + 1, 0));
	vector qs(n + 1, array{ 0, 0, 0 });
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) cin >> v[i][j];
	}
	for (int i = 1; i <= n; i++) {
		char op; cin >> op;
		int a, b; cin >> a >> b;
		qs[i] = array{ a, b, op == 'U' ? 1 : -1 };
	}
	auto res = sol(n, v, qs);
	for (i64 x : res) cout << x << '\n';
}