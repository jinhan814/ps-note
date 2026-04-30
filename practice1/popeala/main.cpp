#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, int k, auto v, auto c) {
	vector psum(m + 1, 0);
	for (int i = 0; i < m; i++) {
		psum[i + 1] = psum[i] + v[i];
	}
	vector prv(n, vector(m + 1, 0));
	for (int iter = 0; iter < n; iter++) {
		for (int i = 1; i <= m; i++) {
			prv[iter][i] = i;
			if (i == 1) continue;
			if (c[iter][i - 1] != c[iter][i - 2]) continue;
			prv[iter][i] = prv[iter][i - 1];
		}
	}
	vector cand(m + 1, vector(0, array{ 0, 0, 0 }));
	for (int i = 1; i <= m; i++) {
		vector buc(1, 1);
		for (int iter = 0; iter < n; iter++) {
			if (c[iter][i - 1] == '0') continue;
			buc.push_back(prv[iter][i]);
		}
		sort(buc.begin(), buc.end());
		buc.push_back(i + 1);
		for (int j = 0; j + 1 < buc.size(); j++) {
			if (buc[j] == buc[j + 1]) continue;
			cand[i].push_back(array{ buc[j], buc[j + 1] - 1, j });
		}
	}
	vector ret(k + 1, 0);
	vector dp(m + 1, 0);
	for (int i = 1; i <= m; i++) {
		auto [l, r, cnt] = cand[i][0];
		dp[i] = cnt * psum[i];
	}
	ret[1] = dp[m];
	for (int iter = 2; iter <= k; iter++) {
		vector ndp(m + 1, 1 << 30);
		vector dq(n + 1, deque(0, pair(0, 0)));
		vector pos(n + 1, 1);
		for (int i = iter; i <= m; i++) {
			for (auto [l, r, cnt] : cand[i]) {
				if (r < iter) continue;
				while (pos[cnt] <= r) {
					int i = pos[cnt]++;
					int val = dp[i - 1] - cnt * psum[i - 1];
					while (dq[cnt].size() && dq[cnt].back().first >= val) {
						dq[cnt].pop_back();
					}
					dq[cnt].push_back(pair(val, i));
				}
				while (dq[cnt].size() && dq[cnt].front().second < max(l, iter)) {
					dq[cnt].pop_front();
				}
				int mn = dq[cnt].front().first;
				ndp[i] = min(ndp[i], mn + cnt * psum[i]);
			}
		}
		dp.swap(ndp);
		ret[iter] = dp[m];
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(m, 0);
	vector c(n, string{});
	for (int i = 0; i < m; i++) cin >> v[i];
	for (int i = 0; i < n; i++) cin >> c[i];
	auto res = sol(n, m, k, v, c);
	for (int i = 1; i <= k; i++) cout << res[i] << '\n';
}