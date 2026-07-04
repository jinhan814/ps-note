#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998'244'353;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

auto sol = [](string s) {
	vector dp(s.size() * 1024 * 3 * 2, -1);
	auto rec = [&](const auto& self, int i, int mask, int val, int f) {
		if (i == s.size()) {
			if (mask == 0) return 0;
			int cnt = 0;
			if (val == 0) cnt++;
			if (mask >> 3 & 1) cnt++;
			if (__builtin_popcount(mask) == 3) cnt++;
			if (cnt != 1) return 0;
			return 1;
		}
		else {
			int& ret = dp[((i * 1024 + mask) * 3 + val) * 2 + f];
			if (ret != -1) return ret;
			ret = 0;
			for (int x = 0; x < 10; x++) {
				if (f == 0 && x > (s[i] - 48)) continue;
				int nmask = mask == 0 && x == 0 ? 0 : mask | 1 << x;
				int nval = (val + x) % 3;
				int nf = f || x < (s[i] - 48);
				ret = add(ret, self(self, i + 1, nmask, nval, nf));
			}
			return ret;
		}
	};
	return rec(rec, 0, 0, 0, 0);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	cout << sol(s) << '\n';
}