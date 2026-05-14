#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector c(0, 0);
	for (int i = 0; i < n; i++) {
		c.push_back(v[i][0]);
		c.push_back(v[i][1]);
	}
	sort(c.begin(), c.end());
	c.erase(unique(c.begin(), c.end()), c.end());
	for (int i = 0; i < n; i++) {
		v[i][0] = lower_bound(c.begin(), c.end(), v[i][0]) - c.begin() + 1;
		v[i][1] = lower_bound(c.begin(), c.end(), v[i][1]) - c.begin() + 1;
	}
	vector dp(20, vector(c.size() + 1, 1 << 30));
	for (int i = 0; i < n; i++) {
		dp[0][v[i][0]] = min(dp[0][v[i][0]], v[i][1]);
	}
	for (int i = c.size(); i >= 2; i--) {
		dp[0][i - 1] = min(dp[0][i - 1], dp[0][i]);
	}
	for (int bit = 1; bit < 20; bit++) {
		for (int i = 1; i <= c.size(); i++){ 
			if (dp[bit - 1][i] >= c.size()) continue;
			dp[bit][i] = dp[bit - 1][dp[bit - 1][i] + 1];
		}
	}
	auto calc = [&](int l, int r) {
		if (l > r) return 0;
		int ret = 0;
		int pos = l;
		for (int bit = 19; bit >= 0; bit--) {
			if (dp[bit][pos] > r) continue;
			ret += 1 << bit;
			pos = dp[bit][pos] + 1;
			if (pos > r) break;
		}
		return ret;
	};
	vector ret(0, 0);
	set s{ pair(0, 0), pair(int(c.size() + 1), int(c.size() + 1)) };
	for (int i = 0; i < n; i++) {
		auto it = s.lower_bound(pair(v[i][0], -1));
		if (it->first <= v[i][1]) continue;
		if (prev(it)->second >= v[i][0]) continue;
		int l = prev(it)->second + 1;
		int r = it->first - 1;
		int v1 = calc(l, r);
		int v2 = calc(l, v[i][0] - 1);
		int v3 = calc(v[i][1] + 1, r);
		if (v1 != v2 + v3 + 1) continue;
		ret.push_back(i);
		s.insert(pair(v[i][0], v[i][1]));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i][0] >> v[i][1];
	auto res = sol(n, v);
	cout << res.size() << '\n';
	for (int x : res) cout << x + 1 << ' ';
	cout << '\n';
}