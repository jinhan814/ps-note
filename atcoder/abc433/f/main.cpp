#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 998'244'353;

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

auto sol = [](string s) {
	vector fac(s.size() + 1, 1);
	for (int i = 1; i <= s.size(); i++) fac[i] = mul(fac[i - 1], i);
	vector inv(s.size() + 1, pow(fac[s.size()], mod - 2));
	for (int i = s.size(); i >= 1; i--) inv[i - 1] = mul(inv[i], i);
	auto bino = [&](int n, int k) {
		if (k == 0 || k == n) return 1;
		return mul(fac[n], mul(inv[k], inv[n - k]));
	};
	vector cnt(s.size(), vector(10, 0));
	for (int i = 0; i < s.size(); i++) {
		if (i > 0) cnt[i] = cnt[i - 1];
		cnt[i][s[i] - 48]++;
	}
	int ret = 0;
	for (int p = 0; p + 1 < s.size(); p++) {
		if (s[p] == 57) continue;
		int a = cnt[p][s[p] - 48];
		int b = cnt[s.size() - 1][s[p] - 47] - cnt[p][s[p] - 47];
		ret = add(ret, bino(a + b - 1, a));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	cout << sol(s) << '\n';
}