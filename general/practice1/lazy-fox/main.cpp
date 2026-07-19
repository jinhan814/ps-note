#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector buc(0, array{ 0, 0, 0 });
	for (int i = 0; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			int dx = v[i][0] - v[j][0];
			int dy = v[i][1] - v[j][1];
			buc.push_back(array{ dx * dx + dy * dy, i, j });
		}
	}
	sort(buc.begin(), buc.end(), greater{});
	vector dp(n + 1, -1); dp[0] = 0;
	vector c(n + 1, -1);
	for (int i = 0, j = 0; i < buc.size(); i = j) {
		vector cand(0, 0);
		while (j < buc.size() && buc[i][0] == buc[j][0]) {
			int a = buc[j][1];
			int b = buc[j][2];
			if (dp[a] != -1 && b != 0) c[b] = max(c[b], dp[a] + 1);
			if (dp[b] != -1 && a != 0) c[a] = max(c[a], dp[b] + 1);
			cand.push_back(a);
			cand.push_back(b);
			j++;
		}
		for (int x : cand) dp[x] = max(dp[x], c[x]);
		for (int x : cand) c[x] = -1;
	}
	int ret = 0;
	for (int i = 1; i <= n; i++) ret = max(ret, dp[i]);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, array{ 0, 0 });
	for (int i = 1; i <= n; i++) cin >> v[i][0] >> v[i][1];
	cout << sol(n, v) << '\n';
}