#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	if (n % 2 == 1) return vector(0, 0);
	int acc = reduce(v.begin() + 1, v.end());
	if (acc % 2 == 1) return vector(0, 0);
	vector dp(n + 1, vector(n / 2 + 1, bitset<90>{}));
	dp[0][0][0] = 1;
	for (int iter = 1; iter <= n; iter++) {
		dp[iter] = dp[iter - 1];
		v[iter] %= 90;
		for (int i = 0; i < n / 2; i++) {
			dp[iter][i + 1] |= dp[iter - 1][i] << v[iter];
			dp[iter][i + 1] |= dp[iter - 1][i] >> (90 - v[iter]);
		}
	}
	if (!dp[n][n / 2][acc / 2 % 90]) return vector(0, 0);
	vector buc(2, vector(0, 0));
	for (int iter = n, i = n / 2, j = acc / 2 % 90; iter >= 1; iter--) {
		if (dp[iter - 1][i][j]) {
			buc[0].push_back(iter);
		}
		else {
			buc[1].push_back(iter);
			i--;
			j -= v[iter];
			if (j < 0) j += 90;
		}
	}
	vector ret(0, 0);
	for (int i = 0; i < n / 2; i++) {
		ret.push_back(buc[0][i]);
		ret.push_back(buc[1][i]);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];
	auto res = sol(n, v);
	if (res.size()) {
		cout << "YES" << '\n';
		for (int x : res) cout << x << ' ';
		cout << '\n';
	}
	else {
		cout << "NO" << '\n';
	}
}