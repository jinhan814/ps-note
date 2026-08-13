#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int q, auto v, auto qs) {
	vector c(n + 1, 0);
	for (int i = 1; i <= n; i++) c[v[i]] = i;
	for (auto& [op, a, b] : qs) {
		if (op == 1) {
			swap(v[a], v[b]);
			swap(c[v[a]], c[v[b]]);
		}
		else {
			swap(v, c);
		}
	}
	return v;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n + 1, 0);
	vector qs(q, array{ 0, 0, 0 });
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (auto& [op, a, b] : qs) {
		cin >> op;
		if (op == 1) cin >> a >> b;
	}
	auto res = sol(n, q, v, qs);
	for (int i = 1; i <= n; i++) cout << res[i] << ' ';
	cout << '\n';
}