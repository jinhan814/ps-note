#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto a, auto b) {
	vector p(n + 1, 0);
	for (int i = 0; i < n; i++) {
		p[i + 1] = p[i] + a[i];
	}
    vector acc(1 << m, 0);
    for (int mask = 0; mask < 1 << m; mask++) {
        for (int i = 0; i < m; i++) {
            if (~mask >> i & 1) continue;
            acc[mask] += b[i];
        }
    }
    vector dp(1 << m, 0);
	for (int mask = 1; mask < 1 << m; mask++) {
		for (int i = 0; i < m; i++) {
			if (~mask >> i & 1) continue;
			int val = dp[mask ^ 1 << i];
			if (acc[mask] == p[val + 1]) val++;
			dp[mask] = max(dp[mask], val);
		}
		if (dp[mask] == n) return true;
	}
	return false;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector a(n, 0), b(m, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < m; i++) cin >> b[i];
	cout << (sol(n, m, a, b) ? "YES" : "NO") << '\n';
}