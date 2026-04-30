#include <bits/stdc++.h>
using namespace std;

auto calc = [](int n, int m, int k, const auto& v) {
	vector psum(n + 1, vector(m + 1, 0));
	vector lo(m + 1, vector(m + 1, 1));
	vector hi(m + 1, vector(m + 1, n));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			psum[i][j] = psum[i][j - 1] + v[i][j];
		}
	}
	for (int s = m; s >= 1; s--) {
		for (int l = 1; l + s - 1 <= m; l++) {
			int r = l + s - 1;
			while (lo[l][r] <= n) {
				if (psum[lo[l][r]][r] - psum[lo[l][r]][l - 1] > k) break;
				lo[l][r]++;
			}
			while (hi[l][r] >= 1) {
				if (psum[hi[l][r]][r] - psum[hi[l][r]][l - 1] > k) break;
				hi[l][r]--;
			}
			if (s > 1) {
				lo[l + 1][r] = max(lo[l + 1][r], lo[l][r]);
				lo[l][r - 1] = max(lo[l][r - 1], lo[l][r]);
				hi[l + 1][r] = min(hi[l + 1][r], hi[l][r]);
				hi[l][r - 1] = min(hi[l][r - 1], hi[l][r]);
			}
		}
	}
	vector c(m + 1, vector(m + 1, false)); c[1][m] = true;
	vector q(1, pair(1, m));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			psum[i][j] = psum[i - 1][j] + v[i][j];
		}
	}
	while (q.size()) {
		auto [l, r] = q.back(); q.pop_back();
		if (l == r) continue;
		if (lo[l][r] > hi[l][r]) continue;
		if (psum[hi[l][r]][l] - psum[lo[l][r] - 1][l] <= k && !c[l + 1][r]) {
			c[l + 1][r] = true;
			q.push_back(pair(l + 1, r));
		}
		if (psum[hi[l][r]][r] - psum[lo[l][r] - 1][r] <= k && !c[l][r - 1]) {
			c[l][r - 1] = true;
			q.push_back(pair(l, r - 1));
		}
	}
	int ret = 1 << 30;
	for (int l = 1; l <= m; l++) {
		for (int r = l; r <= m; r++) {
			if (!c[l][r]) continue;
			if (lo[l][r] <= hi[l][r]) continue;
			ret = min(ret, n + m - (r - l + 1));
		}
	}
	return ret;
};

auto sol = [](int n, int m, int k, const auto& v) {
	vector c(m + 1, vector(n + 1, 0));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) c[j][i] = v[i][j];
	}
	int r1 = calc(n, m, k, v);
	int r2 = calc(m, n, k, c);
	return min(r1, r2);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> k >> m >> n;
	vector v(n + 1, vector(m + 1, 0));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) cin >> v[i][j];
	}
	cout << sol(n, m, k, v) << '\n';
}