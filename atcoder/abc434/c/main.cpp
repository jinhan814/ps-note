#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	int l = m, r = m, p = 0;
	for (auto [x, a, b] : v) {
		l = max(l - (x - p), a);
		r = min(r + (x - p), b);
		p = x;
		if (l > r) return false;
	}
	return true;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n, m; cin >> n >> m;
		vector v(n, array{ 0, 0, 0 });
		for (auto& [x, a, b] : v) cin >> x >> a >> b;
		cout << (sol(n, m, v) ? "Yes" : "No") << '\n';
	}
}