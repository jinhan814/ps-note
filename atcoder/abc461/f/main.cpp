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

auto sol = [](i64 n) {
	vector d(0, i64(0));
	for (i64 i = 1; i * i <= n; i++) {
		if (n % i != 0) continue;
		d.push_back(i);
	}
	for (int i = d.size() - 1; i >= 0; i--) {
		if (d[i] * d[i] == n) continue;
		d.push_back(n / d[i]);
	}
	vector dp1(15, vector(d.size(), 0)); dp1[0][0] = 1;
	vector dp2(15, vector(d.size(), 0));
	for (int iter = 0; iter < d.size(); iter++) {
		for (int i = d.size() - 1; i >= iter; i--) {
			if (d[i] % d[iter] != 0) continue;
			int j = lower_bound(d.begin(), d.end(), d[i] / d[iter]) - d.begin();
			for (int k = 14; k >= 1; k--) {
				dp1[k][i] = add(dp1[k][i], dp1[k - 1][j]);
				dp2[k][i] = add(dp2[k][i], dp2[k - 1][j]);
				dp2[k][i] = add(dp2[k][i], mul(dp1[k - 1][j], d[iter] % mod));
			}
		}
	}
	int ret = 0, fac = 1;
	for (int i = 1; i <= 14; i++) {
		fac = mul(fac, i);
		ret = add(ret, mul(dp2[i].back(), fac));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	i64 n; cin >> n;
	cout << sol(n) << '\n';
}