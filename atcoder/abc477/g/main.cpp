#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int q, auto v, auto adj, auto qs) {
	vector dep(n + 1, 0);
	vector sp(18, vector(n + 1, 0));
	vector in(n + 1, -1), out(n + 1, -1), d(0, 0);
	auto rec = [&](const auto& self, int cur, int prv) -> void {
		in[cur] = d.size();
		d.push_back(cur);
		for (int nxt : adj[cur]) {
			if (nxt == prv) continue;
			dep[nxt] = dep[cur] + 1;
			sp[0][nxt] = cur;
			for (int i = 1; i <= 17; i++) {
				sp[i][nxt] = sp[i - 1][sp[i - 1][nxt]];
			}
			self(self, nxt, cur);
		}
		out[cur] = d.size();
		d.push_back(cur);
	};
	rec(rec, 1, -1);
	auto lca = [&](int a, int b) {
		if (dep[a] < dep[b]) swap(a, b);
		for (int i = 17; i >= 0; i--) {
			if (~(dep[a] - dep[b]) >> i & 1) continue;
			a = sp[i][a];
		}
		if (a == b) return a;
		for (int i = 17; i >= 0; i--) {
			if (sp[i][a] == sp[i][b]) continue;
			a = sp[i][a];
			b = sp[i][b];
		}
		return sp[0][a];
	};
	vector buc(0, array{ 0, 0, 0, 0 });
	for (int i = 0; i < q; i++) {
		auto [a, b, l, r] = qs[i];
		if (in[a] > in[b]) swap(a, b);
		int u = lca(a, b);
		if (u == a) buc.push_back(array{ i, in[a], in[b], -1 });
		else buc.push_back(array{ i, out[a], in[b], u });
	}
	sort(buc.begin(), buc.end(), [](auto a, auto b) {
		if (a[1] / 400 != b[1] / 400) return a[1] < b[1];
		if (a[1] / 400 % 2) return a[2] < b[2];
		return a[2] > b[2];
	});
	vector c(n + 1, false);
	vector cnt(n + 1, 0);
	vector psum(n + 1, n);
	auto update = [&](int i) {
		if (!c[i]) {
			c[i] = true;
			psum[cnt[v[i]]]--;
			cnt[v[i]]++;
		}
		else {
			c[i] = false;
			cnt[v[i]]--;
			psum[cnt[v[i]]]++;
		}
	};
	int l = 0, r = -1;
	vector ret(q, -1);
	for (auto [i, v1, v2, v3] : buc) {
		while (l > v1) update(d[--l]);
		while (r < v2) update(d[++r]);
		while (l < v1) update(d[l++]);
		while (r > v2) update(d[r--]);
		if (v3 != -1) update(v3);
		ret[i] = psum[qs[i][3]] - psum[qs[i][2] - 1];
		if (v3 != -1) update(v3);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n + 1, 0);
	vector adj(n + 1, vector(0, 0));
	vector qs(q, array{ 0, 0, 0, 0 });
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for (auto& [a, b, l, r] : qs) cin >> a >> b >> l >> r;
	auto res = sol(n, q, v, adj, qs);
	for (int x : res) cout << x << '\n';
}