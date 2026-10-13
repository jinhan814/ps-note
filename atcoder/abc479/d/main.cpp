#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int q, auto l, auto r, auto qs) {
	vector dp1(n + 1, 1 << 30);
	vector dp2(n + 1, 1 << 30);
	for (int i = 2; i <= n; i++) dp1[i] = min(dp1[i - 1], r[i - 1]);
	for (int i = n - 1; i >= 1; i--) dp2[i] = min(dp2[i + 1], l[i + 1]);
	vector ret(q, 0);
	for (int i = 0; i < q; i++) {
		auto [a, b] = qs[i];
		if (a < b) ret[i] = min(r[a], l[a] + dp1[a]);
		else ret[i] = min(l[a], r[a] + dp2[a]);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector l(n + 1, 0), r(n + 1, 0);
	vector qs(q, array{ 0, 0 });
	for (int i = 2; i <= n; i++) cin >> l[i];
	for (int i = 1; i <= n - 1; i++) cin >> r[i];
	for (int i = 0; i < q; i++) cin >> qs[i][0] >> qs[i][1];
	auto res = sol(n, q, l, r, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}