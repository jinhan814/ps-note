#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto v) {
	sort(v.begin(), v.end(), [&](auto a, auto b) {
		return a[0] + a[1] < b[0] + b[1];
	});
	i64 acc = 0;
	for (int i = 0; i < n; i++) acc += v[i][1];
	int ret = 0;
	while (ret < n && acc >= v[ret][0] + v[ret][1]) {
		acc -= v[ret][0] + v[ret][1];
		ret++;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		vector v(n, array{ 0, 0 });
		for (auto& [a, b] : v) cin >> a >> b;
		cout << sol(n, v) << '\n';
	}
}