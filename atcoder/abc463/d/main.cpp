#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int k, auto v) {
	sort(v.begin(), v.end(), [](auto a, auto b) {
		return a[1] < b[1];
	});
	auto check = [&](int mid) {
		int cnt = 1;
		int prv = v[0][1];
		for (int i = 1; i < n; i++) {
			if (v[i][0] < prv + mid) continue;
			cnt++;
			prv = v[i][1];
		}
		return cnt >= k;
	};
	int lo = 0, hi = 1 << 30;
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (check(mid)) lo = mid;
		else hi = mid;
	}
	if (lo == 0) lo = -1;
	return lo;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector v(n, array{ 0, 0 });
	for (auto& [a, b] : v) cin >> a >> b;
	cout << sol(n, k, v) << '\n';
}