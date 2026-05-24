#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int q, auto qs) {
	vector p(n + 1, -1);
	vector c(n + 1, 0);
	vector d(n + 1, 0);
	auto find = [&](const auto& self, int i) -> int {
		if (p[i] < 0) return i;
		if (p[p[i]] < 0) return p[i];
		int ret = self(self, p[i]);
		d[i] ^= d[p[i]];
		p[i] = ret;
		return ret;
	};
	vector ret(q, -1);
	int acc = 0;
	for (int i = 0; i < q; i++) {
		auto [a, b] = qs[i];
		int pa = find(find, a);
		int pb = find(find, b);
		if (pa == pb) {
			if (d[a] == d[b]) break;
			ret[i] = acc;
		}
		else {
			acc -= min(c[pa], -p[pa] - c[pa]);
			acc -= min(c[pb], -p[pb] - c[pb]);
			if (d[a] == d[b]) {
				p[pa] += p[pb];
				c[pa] += -p[pb] - c[pb];
				p[pb] = pa;
				d[pb] = 1;
			}
			else {
				p[pa] += p[pb];
				c[pa] += c[pb];
				p[pb] = pa;
				d[pb] = 0;
			}
			acc += min(c[pa], -p[pa] - c[pa]);
			ret[i] = acc;
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector qs(q, array{ 0, 0 });
	for (int i = 0; i < q; i++) cin >> qs[i][0] >> qs[i][1];
	auto res = sol(n, q, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}