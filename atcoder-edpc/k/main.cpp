#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int k, auto v) {
	vector dp(k + 1, false);
	for (int i = 1; i <= k; i++) {
		for (int x : v) {
			if (x > i) break;
			if (dp[i - x]) continue;
			dp[i] = true;
			break;
		}
	}
	if (dp[k]) return true;
	return false;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << (sol(n, k, v) ? "First" : "Second") << '\n';
}