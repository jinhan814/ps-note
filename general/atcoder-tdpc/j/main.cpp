#include <bits/stdc++.h>
using namespace std;

using f64 = double;

auto sol = [](int s) {
	vector dp(s + 1, f64(-1));
	auto rec = [&](const auto& self, int mask) -> f64 {
		if (mask == 0) return 0;
		f64& ret = dp[mask];
		if (ret != -1) return ret;
		ret = 1e100;
		for (int i = 0; i <= 15; i++) {
			bool f1 = (mask << 1) >> i & 1;
			bool f2 = mask >> i & 1;
			bool f3 = mask >> (i + 1) & 1;
			int cnt = f1 + f2 + f3;
			if (cnt == 0) continue;
			f64 val = 0;
			if (f1) val += self(self, mask ^ 1 << (i - 1));
			if (f2) val += self(self, mask ^ 1 << i);
			if (f3) val += self(self, mask ^ 1 << (i + 1));
			val = (3 + val) / cnt;
			ret = min(ret, val);
		}
		return ret;
	};
	return rec(rec, s);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	int s = 0;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		s |= 1 << x;
	}
	cout << fixed << setprecision(20);
	cout << sol(s) << '\n';
}