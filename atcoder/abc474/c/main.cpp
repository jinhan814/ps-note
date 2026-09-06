#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int q, auto v, auto qs) {
	vector ret(0, 0);
	vector c(n + 1, false);
	for (int i = q - 1; i >= 0; i--) {
		if (c[qs[i]]) continue;
		ret.push_back(qs[i]);
		c[qs[i]] = true;
	}
	for (int i = n - 1; i >= 0; i--) {
		if (c[v[i]]) continue;
		ret.push_back(v[i]);
		c[v[i]] = true;
	}
	reverse(ret.begin(), ret.end());
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n, 0);
	vector qs(q, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	for (int i = 0; i < q; i++) cin >> qs[i];
	auto res = sol(n, q, v, qs);
	for (int i = 0; i < n; i++) cout << res[i] << ' ';
	cout << '\n';
}