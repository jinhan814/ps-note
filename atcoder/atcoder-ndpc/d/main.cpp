#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](i64 n) {
	map dp{ pair(i64(0), 0), pair(i64(1), 1) };
	auto rec = [&](const auto& self, i64 n) -> i64 {
		if (dp.count(n)) return dp[n];
		i64 v1 = self(self, n / 10) + n % 10;
		i64 v2 = self(self, n / 10 + 1) + 10 - n % 10;
		return dp[n] = min(v1, v2);
	};
	return rec(rec, n);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		i64 n; cin >> n;
		cout << sol(n) << '\n';
	}
}