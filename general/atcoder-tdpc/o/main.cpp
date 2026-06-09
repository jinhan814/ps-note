#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 1'000'000'007;

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

auto sol = [](auto v) {
	sort(v.begin(), v.end(), greater{});
	while (v.back() == 0) v.pop_back();
	reverse(v.begin(), v.end());
	vector fac(252, 1);
	for (int i = 1; i <= 251; i++) fac[i] = mul(fac[i - 1], i);
	vector inv(252, pow(fac[251], mod - 2));
	for (int i = 251; i >= 1; i--) inv[i - 1] = mul(inv[i], i);
	auto bino = [&](int n, int k) {
		if (k == 0 || k == n) return 1;
		return mul(fac[n], mul(inv[k], inv[n - k]));
	};
	int acc = v[0];
	vector dp(acc + 1, 0); dp[acc - 1] = 1;
	for (int iter = 1; iter < v.size(); iter++) {
		int nacc = acc + v[iter];
		vector ndp(nacc + 1, 0);
		for (int i = 0; i <= acc; i++) {
			if (dp[i] == 0) continue;
			for (int a = 0; a <= min(v[iter], i); a++) {
				for (int b = 0; b <= min(v[iter] - a, acc + 1 - i); b++) {
					if (a + b == 0) continue;
					int val = dp[i];
					val = mul(val, bino(i, a));
					val = mul(val, bino(acc + 1 - i, b));
					val = mul(val, bino(v[iter] - 1, a + b - 1));
					int j = (i - a) + (v[iter] - a - b);
					ndp[j] = add(ndp[j], val);
				}
			}
		}
		acc = nacc;
		dp.swap(ndp);
	}
	return dp[0];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	vector v(26, 0);
	for (int i = 0; i < 26; i++) cin >> v[i];
	cout << sol(v) << '\n';
}