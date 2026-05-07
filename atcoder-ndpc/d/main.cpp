#include <bits/stdc++.h>
using namespace std;

auto sol = [](string s) {
	vector dp(s.size(), array{ -1, -1 });
	auto rec = [&](const auto& self, int i, int f) -> int {
		if (i < 0) return f;
		int& ret = dp[i][f];
		if (ret != -1) return ret;
		int x = s[i] - 48 + f;
		int v1 = x + self(self, i - 1, 0);
		int v2 = 10 - x + self(self, i - 1, 1);
		ret = min(v1, v2);
		return ret;
	};
	return rec(rec, s.size() - 1, 0);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		string s; cin >> s;
		cout << sol(s) << '\n';
	}
}