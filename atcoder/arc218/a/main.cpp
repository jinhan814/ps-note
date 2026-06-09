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

auto sol = [](int n, int m, auto v) {
	vector c(n, map{ pair(0, 0) });
	for (int i = 0; i < n; i++) {
		sort(v[i].begin(), v[i].end());
		for (int l = 0, r = 0; l < m; l = r) {
			while (r < m && v[i][l] == v[i][r]) r++;
			c[i][v[i][l]] = r - l;
		}
		v[i].erase(unique(v[i].begin(), v[i].end()), v[i].end());
	}
	int ret = 0;
	vector acc(n * m + 1, 1);
	vector cnt(n * m + 1, 0);
	for (int i = 0; i < n; i++) {
		for (int x : v[i]) {
			int val = c[i][x];
			val = mul(val, acc[x]);
			val = mul(val, pow(m, (n - i - 1) + i - cnt[x]));
			ret = add(ret, val);
			acc[x] = mul(acc[x], m - c[i][x]);
			cnt[x]++;
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, vector(m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) cin >> v[i][j];
	}
	cout << sol(n, m, v) << '\n';
}