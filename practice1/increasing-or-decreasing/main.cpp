#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto a, auto b) {
	vector ret(0, array{ 0, 0, 0 });
	auto push = [&](int l, int r, int f) {
		ret.push_back(array{ l, r, f });
		sort(a.begin() + l, a.begin() + r + 1);
		if (f) reverse(a.begin() + l, a.begin() + r + 1);
	};
	push(0, n - 1, 0);
	for (int i = 0; i < n - 1; i++) {
		int p = find(a.begin() + i, a.end(), b[i]) - a.begin();
		int mn = *min_element(a.begin() + i, a.begin() + p + 1);
		int mx = *max_element(a.begin() + i, a.begin() + p + 1);
		if (b[i] == mn) push(i, p, 0);
		else if (b[i] == mx) push(i, p, 1);
		else assert(0);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector a(n, 0), b(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];
	auto res = sol(n, a, b);
	cout << res.size() << '\n';
	for (auto [l, r, f] : res) {
		cout << l + 1 << ' ' << r + 1 << ' ' << "ID"[f] << '\n';
	}
}