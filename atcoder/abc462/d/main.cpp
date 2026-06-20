#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, auto v) {
	vector p(1'000'002, 0);
	for (auto [a, b] : v) {
		if (b - a < m) continue;
		p[a]++;
		p[b - m + 1]--;
	}
	i64 ret = 0;
	for (int i = 1; i <= 1'000'000; i++) {
		p[i] += p[i - 1];
		ret += i64(p[i]) * (p[i] - 1) / 2;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, array{ 0, 0 });
	for (auto& [a, b] : v) cin >> a >> b;
	cout << sol(n, m, v) << '\n';
}