#include <bits/stdc++.h>
using namespace std;

auto calc = [](int n, string s) {
	vector z(n, 0); z[0] = n;
	for (int i = 1, l = -1, r = -1; i < n; i++) {
		if (i <= r) z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
		if (r < i + z[i] - 1) l = i, r = i + z[i] - 1;
	}
	return z;
};

auto sol = [](int n, string s) {
	auto z = calc(n, s);
	int ret = 1 << 30;
	for (int cnt = 0; cnt <= 20; cnt++) {
		if (n % ((1 << cnt) + 1) != 0) continue;
		int len = n / ((1 << cnt) + 1);
		vector dp(len + 1, vector(cnt + 1, 1 << 30));
		dp[0][0] = 0;
		for (int i = 0; i <= len; i++) {
			for (int j = 0; j <= cnt; j++) {
				if (dp[i][j] == 1 << 30) continue;
				int p = i + (len << j);
				if (i < len && s[i] == s[p]) {
					dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 1);
				}
				if (i <= len / 2 && j < cnt && z[i] >= i && z[p] >= p) {
					dp[i * 2][j + 1] = min(dp[i * 2][j + 1], dp[i][j] + 1);
				}
			}
		}
		ret = min(ret, dp[len][cnt]);
	}
	if (ret == 1 << 30) ret = -1;
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string s; cin >> s;
	cout << sol(n, s) << '\n';
}