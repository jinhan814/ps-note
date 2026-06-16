#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1'000'000'007;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

auto sol = [](int n, int m, auto v) {
	vector c(512, false);
	for (int i = 0; i < n; i++) {
		int x = 0;
		for (char c : v[i]) x = (x << 1) | (c == '1');
		c[x | (1 << v[i].size())] = true;
	}
	vector dp(128, vector(256, 0));
	dp[0][1] = 1;
	for (int iter = 1; iter <= m; iter++) {
		vector ndp(128, vector(256, 0));
		for (int mask = 0; mask < 128; mask++) {
			for (int s = 1; s < 256; s++) {
				if (dp[mask][s] == 0) continue;
				for (int x = 0; x <= 1; x++) {
					int nmask = mask << 1 | x;
					int ns = (s << 1) & 255;
					for (int i = 0; i < 8; i++) {
						if (~s >> i & 1) continue;
						if (!c[(nmask & ((1 << (i + 1)) - 1)) | (1 << (i + 1))]) continue;
						ns |= 1;
						break;
					}
					nmask &= 127;
					ndp[nmask][ns] = add(ndp[nmask][ns], dp[mask][s]);
				}
			}
		}
		dp.swap(ndp);
	}
	int ret = 0;
	for (int mask = 0; mask < 128; mask++) {
		for (int s = 1; s < 256; s += 2) {
			ret = add(ret, dp[mask][s]);
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}