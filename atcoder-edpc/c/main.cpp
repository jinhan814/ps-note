#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	array dp{ 0, 0, 0 };
	for (auto [a, b, c] : v) {
		array ndp{ 0, 0, 0 };
		ndp[0] = max(dp[1], dp[2]) + a;
		ndp[1] = max(dp[0], dp[2]) + b;
		ndp[2] = max(dp[0], dp[1]) + c;
		dp.swap(ndp);
	}
	return *max_element(dp.begin(), dp.end());
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0, 0 });
	for (auto& [a, b, c] : v) cin >> a >> b >> c;
	cout << sol(n, v) << '\n';
}