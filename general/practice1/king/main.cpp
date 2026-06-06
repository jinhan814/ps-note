#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto modmul = [](int a, int b, int mod) {
	return i64(a) * b % mod;
};

auto modpow = [](int x, int n, int mod) {
	int ret = 1;
	for (; n; n >>= 1) {
		if (n & 1) ret = modmul(ret, x, mod);
		x = modmul(x, x, mod);
	}
	return ret;
};

auto sol = [](int n, auto v, int mod) {
	map c{ pair(0, 0) };
	for (int i = 1; i < n; i++) {
		int x = modpow(v[i], mod - 2, mod);
		c[modmul(v[i - 1], x, mod)]++;
		if (i > 1) c[modmul(v[i - 2], x, mod)]++;
	}
	int ret = -1;
	for (auto [x, cnt] : c) {
		if (4 * cnt < n - 4) continue;
		map dp{ pair(0, 0) }; dp.clear();
		for (int i = 0; i < n; i++) {
			int v1 = modmul(v[i], x, mod);
			int v2 = dp[v1] + 1;
			dp[v[i]] = v2;
			if (2 * v2 >= n) ret = max(ret, v2);
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n, mod; cin >> n >> mod;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << sol(n, v, mod) << '\n';
	}
}