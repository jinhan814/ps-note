#include <bits/stdc++.h>
using namespace std;

constexpr int sz = 1'000;

auto sol = [](int n, auto v) {
	vector dp1(2 * sz + 1, 1 << 30);
	vector dp2(2 * sz + 1, 1 << 30);
	dp1[sz] = 0;
	dp2[sz] = 0;
	for (int iter = 1; iter <= n; iter++) {
		auto [x1, y1] = v[iter - 1];
		auto [x2, y2] = v[iter];
		vector ndp1(2 * sz + 1, 1 << 30);
		vector ndp2(2 * sz + 1, 1 << 30);
		for (int i = 0; i <= 2 * sz; i++) {
			ndp1[i] = min(ndp1[i], dp1[i] + abs(x2 - x1));
			ndp2[x1 + sz] = min(ndp2[x1 + sz], dp1[i] + abs(y2 + sz - i));
			ndp2[i] = min(ndp2[i], dp2[i] + abs(y2 - y1));
			ndp1[y1 + sz] = min(ndp1[y1 + sz], dp2[i] + abs(x2 + sz - i));
		}
		dp1.swap(ndp1);
		dp2.swap(ndp2);
	}
	int ret = 1 << 30;
	for (int i = 0; i <= 2 * sz; i++) {
		ret = min(ret, dp1[i]);
		ret = min(ret, dp2[i]);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, array{ 0, 0 });
	for (int i = 1; i <= n; i++) cin >> v[i][0] >> v[i][1];
	cout << sol(n, v) << '\n';
}