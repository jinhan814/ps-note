#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 1e9 + 7;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int mul(int a, int b) {
	return i64(a) * b % mod;
}

constexpr int pow(int x, int n) {
	int ret = 1;
	for (; n; n >>= 1) {
		if (n & 1) ret = mul(ret, x);
		x = mul(x, x);
	}
	return ret;
}

auto sol = [](string s, int q, auto qs) {
	vector fac(s.size() + 1, 1);
	for (int i = 1; i <= s.size(); i++) fac[i] = mul(fac[i - 1], i);
	vector inv(s.size() + 1, pow(fac[s.size()], mod - 2));
	for (int i = s.size(); i >= 1; i--) inv[i - 1] = mul(inv[i], i);
	auto bino = [&](int n, int k) {
		if (k == 0 || k == n) return 1;
		return mul(fac[n], mul(inv[k], inv[n - k]));
	};
	vector dp(s.size() + 1, vector(26, vector(26, 0)));
	vector cnt(26, 0);
	for (int iter = s.size() - 1; iter >= 0; iter--) {
		int a = s[iter] - 'a';
		for (int b = 0; b < 26; b++) {
			if (cnt[b] == 0) continue;
			for (int i = 0; i <= iter; i++) {
				int v1 = bino(iter, i);
				int v2 = cnt[b];
				dp[i + 2][a][b] = add(dp[i + 2][a][b], mul(v1, v2));
			}
		}
		cnt[s[iter] - 'a']++;
	}
	vector ret(q, 0);
	for (int i = 0; i < q; i++) {
		auto [a, b] = qs[i];
		ret[i] = dp[a][b[0] - 'a'][b[1] - 'a'];
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	int q; cin >> q;
	vector qs(q, pair(0, string{}));
	for (auto& [a, b] : qs) cin >> a >> b;
	auto res = sol(s, q, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}