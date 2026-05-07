#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1'000'000'007;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

auto sol = [](string s, int k) {
	vector dp(s.size(), vector(k, array{ -1, -1 }));
	auto rec = [&](const auto& self, int i, int j, int f) -> int {
		if (i == s.size()) return j == 0;
		int& ret = dp[i][j][f];
		if (ret != -1) return ret;
		ret = 0;
		for (int x = 0; x < 10; x++) {
			if (f == 0 && x > s[i] - 48) break;
			int val = self(self, i + 1, (j + x) % k, f || x < s[i] - 48);
			ret = add(ret, val);
		}
		return ret;
	};
	return add(rec(rec, 0, 0, 0), mod - 1);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	int k; cin >> k;
	cout << sol(s, k) << '\n';
}