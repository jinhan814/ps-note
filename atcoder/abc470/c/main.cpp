#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int q, auto qs) {
	vector ret(q, 0);
	vector v(n + 1, 0), c(0, 0);
	int acc = 0;
	for (int iter = 0; iter < q; iter++) {
		auto [op, p] = qs[iter];
		if (op == 1) {
			acc ^= v[p];
			v[p]++;
			acc ^= v[p];
			if (v[p] == 1) c.push_back(p);
		}
		else {
			vector nc(0, 0);
			for (int p : c) {
				acc ^= v[p];
				v[p]--;
				acc ^= v[p];
				if (v[p] != 0) nc.push_back(p);
			}
			c.swap(nc);
		}
		ret[iter] = acc;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector qs(q, array{ 0, 0 });
	for (auto& [op, p] : qs) {
		cin >> op;
		if (op == 1) cin >> p;
	}
	auto res = sol(n, q, qs);
	for (int x : res) cout << x << '\n';
}