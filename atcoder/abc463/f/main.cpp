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

auto sol = [](int n, auto v) {
	vector fac(n + 1, 1);
	for (int i = 1; i <= n; i++) fac[i] = mul(fac[i - 1], i);
	vector inv(n + 1, pow(fac[n], mod - 2));
	for (int i = n; i >= 1; i--) inv[i - 1] = mul(inv[i], i);
	auto bino = [&](int n, int k) {
		if (k == 0 || k == n) return 1;
		return mul(fac[n], mul(inv[k], inv[n - k]));
	};
	map cache{ pair(pair(0, 0), 0) }; cache.clear();
	auto calc = [&](int a, int b) {
		if (cache.count(pair(a, b))) return cache[pair(a, b)];
		int ret = 0;
		for (int i = 0; i <= a; i++) {
			int v1 = bino(a, i);
			int v2 = pow(b + i, mod - 2);
			ret = add(ret, mul(v1, v2));
		}
		return cache[pair(a, b)] = ret;
	};
	vector f(n, false);
	for (int i = 0; i < n; i++) {
		if (v[i][0] <= v[i][1]) continue;
		f[i] = true;
		swap(v[i][0], v[i][1]);
	}
	vector cnt(2 * n + 2, array{ 0, 0, 0 });
	int mx = -1, smx = -1;
	for (int i = 0; i < n; i++) {
		cnt[v[i][1]][clamp(abs(v[i][0] - v[i][1]), 0, 2)]++;
		if (smx == -1 || v[smx][1] < v[i][1]) smx = i;
		if (mx == -1 || v[mx][1] < v[smx][1]) swap(mx, smx);
	}
	vector ret(n, array{ 0, 0 });
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2; j++) {
			for (int bias = 0; bias <= 1; bias++) {
				int val = v[i][j] + bias;
				if (v[i][j ^ 1] + (1 - bias) > val) continue;
				if (mx != -1 && mx != i && v[mx][1] > val) continue;
				if (smx != -1 && smx != i && v[smx][1] > val) continue;
				if (cnt[val][0] - (v[i][0] == v[i][1] && bias == 0) != 0) continue;
				int v1 = cnt[val - 1][1] + cnt[val - 1][2];
				int v2 = cnt[val][2];
				int v3 = cnt[val - 1][0];
				int v4 = cnt[val][1];
				if (v[i][0] <= val - 2 && v[i][1] == val - 1) v1--;
				if (v[i][0] <= val - 2 && v[i][1] == val) v2--;
				if (v[i][0] == val - 1 && v[i][1] == val - 1) v3--;
				if (v[i][0] == val - 1 && v[i][1] == val) v4--;
				int acc = v2 + v3 + 2 * v4 + 1;
				if (v[i][j] + bias == v[i][j ^ 1] + (1 - bias)) acc++;
				int res = calc(v1, acc);
				res = mul(res, pow(pow(2, v1), mod - 2));
				res = mul(res, pow(pow(2, v2 + v4 + 1), mod - 2));
				ret[i][j] = add(ret[i][j], res);
			}
		}
		if (f[i]) swap(ret[i][0], ret[i][1]);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0 });
	for (auto& [a, b] : v) cin >> a >> b;
	auto res = sol(n, v);
	for (auto [a, b] : res) cout << a << ' ' << b << ' ';
	cout << '\n';
}