#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 998'244'353;

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

auto get_spf = [](int n) {
	vector s(n + 1, true);
	vector p(n + 1, 0);
	for (int i = 2; i * i <= n; i++) {
		if (!s[i]) continue;
		for (int j = i * i; j <= n; j += i) {
			s[j] = false;
			if (p[j] == 0) p[j] = i;
		}
	}
	for (int i = 2; i <= n; i++) {
		if (!s[i]) continue;
		p[i] = i;
	}
	return p;
};

auto factor = [p = get_spf(10'000'000)](int n) {
	vector ret(0, pair(0, 0));
	while (n > 1) {
		int val = p[n], cnt = 0;
		while (n % val == 0) n /= val, cnt++;
		ret.push_back(pair(val, cnt));
	}
	return ret;
};

auto sol = [](int n, auto v) {
	vector buc(n, vector(0, pair(0, 0)));
	vector c(0, 0);
	for (int i = 0; i < n; i++) {
		buc[i] = factor(v[i]);
		for (auto [val, cnt] : buc[i]) c.push_back(val);
	}
	sort(c.begin(), c.end());
	c.erase(unique(c.begin(), c.end()), c.end());
	vector mx(c.size(), 0), smx(c.size(), 0);
	for (int i = 0; i < n; i++) {
		for (auto [val, cnt] : buc[i]) {
			int p = lower_bound(c.begin(), c.end(), val) - c.begin();
			if (smx[p] < cnt) smx[p] = cnt;
			if (mx[p] < smx[p]) swap(mx[p], smx[p]);
		}
	}
	int acc = 1;
	for (int i = 0; i < c.size(); i++) {
		int val = pow(c[i], mx[i]);
		acc = mul(acc, val);
	}
	vector ret(n, 0);
	for (int i = 0; i < n; i++) {
		ret[i] = acc;
		for (auto [val, cnt] : buc[i]) {
			int p = lower_bound(c.begin(), c.end(), val) - c.begin();
			if (mx[p] != cnt) continue;
			if (mx[p] == smx[p]) continue;
			int x = pow(val, mx[p] - smx[p]);
			ret[i] = mul(ret[i], pow(x, mod - 2));
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		auto res = sol(n, v);
		for (int i = 0; i < n; i++) cout << res[i] << ' ';
		cout << '\n';
	}
}