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

auto sol = [](int n, i64 m, auto v) {
	vector fac(n + 1, 1);
	for (int i = 1; i <= n; i++) {
		fac[i] = mul(fac[i - 1], i);
	}
	vector buc(n / 2 + 1, vector(0, i64(0)));
	for (int mask = 0; mask < 1 << (n / 2); mask++) {
		int v1 = 0;
		i64 v2 = 0;
		for (int i = 0; i < n / 2; i++) {
			if (~mask >> i & 1) continue;
			v1++;
			v2 += v[i];
		}
		buc[v1].push_back(v2);
	}
	vector psum(n / 2 + 1, vector(0, 0));
	for (int i = 0; i <= n / 2; i++) {
		sort(buc[i].begin(), buc[i].end());
		psum[i].resize(buc[i].size() + 1);
		for (int j = 0; j < buc[i].size(); j++ ){
			psum[i][j + 1] = add(psum[i][j], buc[i][j] % mod);
		}
	}
	vector c1(n + 1, 0);
	vector c2(n + 1, 0);
	for (int mask = 0; mask < 1 << ((n + 1) / 2); mask++) {
		int v1 = 0;
		i64 v2 = 0;
		for (int i = 0; i < (n + 1) / 2; i++ ){
			if (~mask >> i & 1) continue;
			v1++;
			v2 += v[i + n / 2];
		}
		for (int i = 0; i <= n / 2; i++) {
			int p = lower_bound(buc[i].begin(), buc[i].end(), m - v2) - buc[i].begin();
			int cnt = buc[i].size() - p;
			c1[v1 + i] = add(c1[v1 + i], cnt);
			c2[v1 + i] = add(c2[v1 + i], sub(psum[i].back(), psum[i][p]));
			c2[v1 + i] = add(c2[v1 + i], mul(cnt, v2 % mod));
		}
	}
	int acc = 0;
	for (int i = 0; i < n; i++) {
		acc = add(acc, v[i] % mod);
	}
	int ret = 0;
	for (int k = 1; k <= n; k++) {
		int val = mul(c2[k], k);
		val = sub(val, mul(c2[k - 1], n - k));
		val = sub(val, mul(c1[k - 1], acc));
		val = mul(val, fac[k - 1]);
		val = mul(val, fac[n - k]);
		ret = add(ret, val);
	}
	ret = mul(ret, pow(fac[n], mod - 2));
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	i64 m; cin >> m;
	vector v(n, i64(0));
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}