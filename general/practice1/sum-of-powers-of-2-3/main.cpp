#include <bits/stdc++.h>
using namespace std;

auto sol(int n) {
	vector ret(0, pair(0, 0));
	auto rec = [&](const auto& self, int n, int a, int b) -> void {
		while (n % 2 == 0) a++, n /= 2;
		while (n % 3 == 0) b++, n /= 3;
		int cnt = 0, val = 1;
		while (n >= 3 * val) cnt++, val *= 3;
		ret.push_back(pair(a, b + cnt));
		if (n - val != 0) self(self, n - val, a, b);
	};
	rec(rec, n, 0, 0);
	return ret;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int iter = 1; iter <= tc; iter++) {
		int n; cin >> n;
		auto res = sol(n);
		cout << iter << ' ' << res.size();
		for (auto [a, b] : res) cout << " [" << a << ',' << b << ']';
		cout << '\n';
	}
}