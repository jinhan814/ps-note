#include <bits/stdc++.h>
using namespace std;

auto sol = [](string s) {
	vector cache(s.size(), vector(s.size(), -1));
	auto rec = [&](const auto& self, int l, int r) -> int {
		int& ret = cache[l][r];
		if (ret != -1) return ret;
		for (int i = l + 1; i <= r - 1; i += 3) {
			if (s[l] != 'i' || s[i] != 'w' || s[r] != 'i') continue;
			if (l + 1 <= i - 1 && !self(self, l + 1, i - 1)) continue;
			if (i + 1 <= r - 1 && !self(self, i + 1, r - 1)) continue;
			return ret = 1;
		}
		for (int i = l + 2; i <= r - 3; i += 3) {
			if (!self(self, l, i)) continue;
			if (!self(self, i + 1, r)) continue;
			return ret = 1;
		}
		return ret = 0;
	};
	vector dp(s.size(), 0);
	for (int i = 0; i < s.size(); i++) {
		if (i > 0) dp[i] = dp[i - 1];
		for (int j = i - 2; j >= 0; j -= 3) {
			if (!rec(rec, j, i)) continue;
			int val = (i - j + 1) / 3;
			if (j > 0) val += dp[j - 1];
			dp[i] = max(dp[i], val);
		}
	}
	return dp.back();
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	cout << sol(s) << '\n';
}