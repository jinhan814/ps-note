#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int q, auto v, auto qs) {
	vector psum(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		psum[i] = psum[i - 1] + v[i];
	}
	vector ret(0, 0);
	for (auto [op, a, b] : qs) {
		if (op == 1) {
			psum[a] -= v[a];
			psum[a + 1] -= v[a] + v[a + 1];
			swap(v[a], v[a + 1]);
			psum[a] += v[a];
			psum[a + 1] += v[a] + v[a + 1];
		}
		else {
			ret.push_back(psum[b] - psum[a - 1]);
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n + 1, 0);
	vector qs(q, array{ 0, 0, 0 });
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (auto& [op, a, b] : qs) {
		cin >> op >> a;
		if (op == 2) cin >> b;
	}
	auto res = sol(n, q, v, qs);
	for (int x : res) cout << x << '\n';
}