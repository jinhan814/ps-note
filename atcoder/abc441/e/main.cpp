#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct segtree {
	segtree(int n) : sz(1 << (__lg(n - 1 | 1) + 1)), tree(sz << 1) {}
	void update(int i, int x) {
		i |= sz;
		do tree[i] += x; while (i >>= 1);
	}
	int query(int l, int r) const {
		int ret = 0;
		for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret += tree[l++];
			if (~r & 1) ret += tree[r--];
		}
		return ret;
	}
private:
	int sz;
	vector<int> tree;
};

auto sol = [](int n, string s) {
	segtree tree(2 * n);
	tree.update(n, 1);
	i64 ret = 0;
	int acc = 0;
	for (char c : s) {
		if (c == 'A') acc++;
		if (c == 'B') acc--;
		ret += tree.query(0, acc + n - 1);
		tree.update(acc + n, 1);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string s; cin >> s;
	cout << sol(n, s) << '\n';
}