#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, int k, int q, auto v, auto qs) {
	vector tree(1, array{ -1, -1, 0 });
	auto update = [&](string s, int x) {
		int p = 0;
		for (char c : s) {
			tree[p][2] += x;
			if (tree[p][c] == -1) {
				tree[p][c] = tree.size();
				tree.push_back(array{ -1, -1, 0 });
			}
			p = tree[p][c];
		}
		tree[p][2] += x;
	};
	auto query = [&](string s) {
		int ret = 0;
		int p = 0;
		for (char c : s) {
			if (c == 0 && tree[p][1] != -1) ret += tree[tree[p][1]][2];
			p = tree[p][c];
			if (p == -1) break;
		}
		if (p != -1) ret += tree[p][2];
		return ret;
	};
	for (int i = 0; i < n; i++) update(v[i], 1);
	vector ret(q, false);
	for (int i = 0; i < q; i++) {
		auto [a, b] = qs[i];
		update(v[a], -1);
		v[a][b] ^= 1;
		update(v[a], 1);
		if (v[a] == string(m, 0)) continue;
		if (query(v[a]) <= k) ret[i] = true;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> k >> m;
	string s; cin >> s;
	vector v(n, string{});
	for (int i = 0; i < n; i++) {
		cin >> v[i];
		for (int j = 0; j < m; j++) v[i][j] = v[i][j] == s[j];
	}
	int q; cin >> q;
	vector qs(q, array{ 0, 0 });
	for (auto& [a, b] : qs) {
		cin >> a >> b;
		a--;
		b--;
	}
	auto res = sol(n, m, k, q, v, qs);
	for (int i = 0; i < q; i++) {
		cout << (res[i] ? "Yes" : "No") << '\n';
	}
}