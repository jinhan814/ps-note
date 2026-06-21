#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 998'244'353;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int sub(int a, int b) {
	return a < b ? a - b + mod : a - b;
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

auto sol = [](int q, auto qs) {
	int sz = 200'000;
	vector fac(sz + 1, 1);
	for (int i = 1; i <= sz; i++) fac[i] = mul(fac[i - 1], i);
	vector inv(sz + 1, pow(fac[sz], mod - 2));
	for (int i = sz; i >= 1; i--) inv[i - 1] = mul(inv[i], i);
	auto bino = [&](int n, int k) {
		if (k == 0 || k == n) return 1;
		return mul(fac[n], mul(inv[k], inv[n - k]));
	};
	vector ret(q, 0), cand(0, 0);
	for (int i = 0; i < q; i++) {
		auto& [n, x] = qs[i];
		if (x < 0) x = -x;
		if (x >= n) ret[i] = x;
		else cand.push_back(i);
	}
	sort(cand.begin(), cand.end(), [&](int i, int j) {
		if (qs[i][0] / 400 != qs[j][0] / 400) return qs[i][0] < qs[j][0];
		if (qs[i][0] / 400 % 2) return qs[i][0] + qs[i][1] < qs[j][0] + qs[j][1];
		return qs[i][0] + qs[i][1] > qs[j][0] + qs[j][1];
	});
	int a = 1, b = 0, v1 = 1, v2 = 0;
	for (int i : cand) {
		auto [n, x] = qs[i];
		int m = (n + x) / 2;
		while (a < n) {
			v2 = sub(add(mul(v2, 2), v1), mul(b + 1, bino(a, b)));
			v1 = sub(mul(v1, 2), bino(a, b));
			a++;
		}
		while (b > m) {
			v1 = sub(v1, bino(a, b));
			v2 = sub(v2, mul(b, bino(a, b)));
			b--;
		}
		while (a > n) {
			a--;
			v1 = mul(add(v1, bino(a, b)), (mod + 1) / 2);
			v2 = mul(add(sub(v2, v1), mul(b + 1, bino(a, b))), (mod + 1) / 2);
		}
		while (b < m) {
			b++;
			v1 = add(v1, bino(a, b));
			v2 = add(v2, mul(b, bino(a, b)));
		}
		ret[i] = sub(mul(n + x, v1), mul(2, v2));
		ret[i] = mul(ret[i], pow(pow(2, n - 1), mod - 2));
		ret[i] = sub(ret[i], x);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int q; cin >> q;
	vector qs(q, array{ 0, 0 });
	for (int i = 0; i < q; i++) cin >> qs[i][0] >> qs[i][1];
	auto res = sol(q, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}