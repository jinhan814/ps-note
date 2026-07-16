#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int q, auto v, auto qs) {
	vector sp1(30, vector(n + 1, 0));
	vector sp2(30, vector(n + 1, i64(0)));
	for (int i = 1; i <= n; i++) {
		sp1[0][i] = v[i];
		sp2[0][i] = i;
	}
	for (int bit = 1; bit < 30; bit++) {
		for (int i = 1; i <= n; i++) {
			sp1[bit][i] = sp1[bit - 1][sp1[bit - 1][i]];
			sp2[bit][i] = sp2[bit - 1][i] + sp2[bit - 1][sp1[bit - 1][i]];
		}
	}
	vector ret(q, i64(0));
	for (int i = 0; i < q; i++) {
		auto [a, b] = qs[i];
		for (int bit = 29; bit >= 0; bit--) {
			if (~a >> bit & 1) continue;
			ret[i] += sp2[bit][b];
			b = sp1[bit][b];
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n + 1, 0);
	vector qs(q, array{ 0, 0 });
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (int i = 0; i < q; i++) cin >> qs[i][0] >> qs[i][1];
	auto res = sol(n, q, v, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}