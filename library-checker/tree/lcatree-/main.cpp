#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int q, auto par, auto qs) {
	vector dep(n, 0);
	vector sp(19, vector(n, 0));
	for (int i = 1; i < n; i++) {
		dep[i] = dep[par[i]] + 1;
		sp[0][i] = par[i];
	}
	for (int bit = 1; bit <= 18; bit++) {
		for (int i = 0; i < n; i++) {
			sp[bit][i] = sp[bit - 1][sp[bit - 1][i]];
		}
	}
	auto lca = [&](int a, int b) {
		if (dep[a] < dep[b]) swap(a, b);
		for (int bit = 18; bit >= 0; bit--) {
			if (~(dep[a] - dep[b]) >> bit & 1) continue;
			a = sp[bit][a];
		}
		if (a == b) return a;
		for (int bit = 18; bit >= 0; bit--) {
			if (sp[bit][a] == sp[bit][b]) continue;
			a = sp[bit][a];
			b = sp[bit][b];
		}
		return sp[0][a];
	};
	vector ret(q, 0);
	for (int i = 0; i < q; i++) {
		auto [a, b] = qs[i];
		ret[i] = lca(a, b);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector par(n, 0);
	vector qs(q, array{ 0, 0 });
	for (int i = 1; i < n; i++) cin >> par[i];
	for (int i = 0; i < q; i++) cin >> qs[i][0] >> qs[i][1];
	auto res = sol(n, q, par, qs);
	for (int x : res) cout << x << '\n';
}