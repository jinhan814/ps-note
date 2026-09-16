#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	int acc = 0;
	for (int i = 0; i < n; i++) acc += v[i];
	if (acc % n != 0) return vector(1, tuple(-1, -1, -1));
	for (int i = 0; i < n; i++) v[i] -= acc / n;
	vector dp(1 << n, 0);
	for (int mask = 0; mask < 1 << n; mask++) {
		int s = 0;
		for (int i = 0; i < n; i++) {
			if (~mask >> i & 1) continue;
			dp[mask] = max(dp[mask], dp[mask ^ 1 << i]);
			s += v[i];
		}
		if (s == 0) dp[mask]++;
	}
	vector ret(0, tuple(0, 0, 0));
	vector buc(0, 0);
	int mask = (1 << n) - 1;
	auto f = [&] {
		for (int i = 1; i < buc.size(); i++) {
			if (v[buc[i]] <= 0) continue;
			ret.push_back(tuple(buc[i], buc[0], v[buc[i]]));
		}
		for (int i = 1; i < buc.size(); i++) {
			if (v[buc[i]] >= 0) continue;
			ret.push_back(tuple(buc[0], buc[i], -v[buc[i]]));
		}
		buc.clear();
	};
	while (mask != 0) {
		int s = 0;
		for (int i = 0; i < n; i++) {
			if (~mask >> i & 1) continue;
			s += v[i];
		}
		for (int i = 0; i < n; i++) {
			if (~mask >> i & 1) continue;
			if (dp[mask] != dp[mask ^ 1 << i] + (s == 0)) continue;
			buc.push_back(i);
			mask ^= 1 << i;
			if (v[i] == s) f();
			break;
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	auto res = sol(n, v);
	if (res != vector(1, tuple(-1, -1, -1))) {
		cout << res.size() << '\n';
		for (auto [a, b, c] : res) {
			cout << a + 1 << ' ' << b + 1 << ' ' << c << '\n';
		}
	}
	else {
		cout << -1 << '\n';
	}
}