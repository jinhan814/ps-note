#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m) {
	vector dp(n + 1, 0); dp[0] = 1;
	vector s(n + 1, true);
	for (int i = 2; i <= n; i++) {
		if (!s[i]) continue;
		for (int j = i * i; j <= n; j += i) s[j] = false;
		auto ndp = dp;
		for (int p = i; p <= n; p *= i) {
			for (int x = p; x <= n; x++) {
				ndp[x] += i64(p) * dp[x - p] % m;
				if (ndp[x] >= m) ndp[x] -= m;
			}
		}
		dp.swap(ndp);
	}
	int ret = 0;
	for (int x = 0; x <= n; x++) {
		ret += dp[x];
		if (ret >= m) ret -= m;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	cout << sol(n, m) << '\n';
}