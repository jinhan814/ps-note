#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int q, auto qs) {
	vector v(n + 1, 0), c(q + 1, 0);
	int mn = 0;
	vector ret(0, 0);
	for (auto [op, x] : qs) {
		if (op == 1) {
			v[x]++;
			c[v[x]]++;
			if (c[v[x]] == n) mn++;
		}
		else {
			if (x + mn > q) ret.push_back(0);
			else ret.push_back(c[x + mn]);
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector qs(q, array{ 0, 0 });
	for (auto& [op, x] : qs) cin >> op >> x;
	auto res = sol(n, q, qs);
	for (int x : res) cout << x << '\n';
}