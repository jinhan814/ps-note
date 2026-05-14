#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, int q, auto v, auto qs) {
	vector sp(20, vector(n + 1, 1 << 30));
	for (auto [a, b] : v) {
		sp[0][a] = min(sp[0][a], b);
	}
	for (int i = n - 1; i >= 1; i--) {
		sp[0][i] = min(sp[0][i], sp[0][i + 1]);
	}
	for (int bit = 1; bit < 20; bit++) {
		for (int i = 1; i <= n; i++) {
			if (sp[bit - 1][i] >= n) continue;
			sp[bit][i] = sp[bit - 1][sp[bit - 1][i] + 1];
		}
	}
	vector ret(q, 0);
	for (int i = 0; i < q; i++) {
		auto [a, b] = qs[i];
		for (int bit = 19; bit >= 0; bit--) {
			if (sp[bit][a] > b) continue;
			ret[i] += 1 << bit;
			a = sp[bit][a] + 1;
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, q; cin >> n >> m >> q;
	vector v(m, array{ 0, 0 });
	vector qs(q, array{ 0, 0 });
	for (auto& [a, b] : v) cin >> a >> b;
	for (auto& [a, b] : qs) cin >> a >> b;
	auto res = sol(n, m, q, v, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}