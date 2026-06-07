#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 1'000'000'007;

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

auto sol = [](int n, auto v) {
	vector buc(n + 1, vector(0, 0));
	for (int i = 0; i < n; i++) {
		buc[v[i]].push_back(i);
		if (i > 0 && v[i] > v[i - 1] + 1) return 0;
	}
	vector fac(n + 1, 1);
	for (int i = 1; i <= n; i++) fac[i] = mul(fac[i - 1], i);
	vector inv(n + 1, pow(fac[n], mod - 2));
	for (int i = n; i >= 1; i--) inv[i - 1] = mul(inv[i], i);
	auto bino = [&](int n, int k) {
		if (k == 0 || k == n) return 1;
		return mul(fac[n], mul(inv[k], inv[n - k]));
	};
	auto rec = [&](const auto& self, int l, int r) {
		if (l == r) return 1;
		auto it = upper_bound(buc[v[l]].begin(), buc[v[l]].end(), r);
		if (it != buc[v[l]].begin() && *prev(it) > l) {
			int i = *prev(it);
			int ret = bino(r - l, i - l);
			ret = mul(ret, self(self, l, i - 1));
			ret = mul(ret, self(self, i, r));
			return ret;
		}
		else {
			return self(self, l + 1, r);
		}
	};
	return rec(rec, 0, n - 1);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int iter = 1; iter <= tc; iter++) {
		int n; cin >> n;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << "Case #" << iter << ": " << sol(n, v) << '\n';
	}
}