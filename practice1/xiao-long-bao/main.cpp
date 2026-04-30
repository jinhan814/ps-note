#include <bits/stdc++.h>
using namespace std;

auto naive = [](int n, auto a, auto b) {
	vector p(n, 0);
	iota(p.begin(), p.end(), 0);
	int ret = 0;
	do {
		vector v(n, 0);
		int acc = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (p[i] >= p[j]) continue;
				if (a[i] < abs(i - j)) continue;
				acc += b[i];
			}
		}
		ret = max(ret, acc);
	}
	while (next_permutation(p.begin(), p.end()));
	return ret;
};

auto sol = [](int n, auto a, auto b) {
	if (n <= 7) return naive(n, a, b);
	vector cand(0, vector(0, 0));
	vector p(7, 0);
	iota(p.begin(), p.end(), 0);
	do cand.push_back(p);
	while (next_permutation(p.begin(), p.end()));
	vector dp(cand.size(), 0);
	for (int iter = 0; iter < cand.size(); iter++) {
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				if (cand[iter][i] >= cand[iter][j]) continue;
				if (a[i] < abs(i - j)) continue;
				dp[iter] += b[i];
			}
		}
	}
	vector nxt(cand.size(), vector(8, 0));
	for (int iter = 0; iter < cand.size(); iter++) {
		for (int k = 0; k <= 7; k++) {
			vector v(7, k);
			for (int i = 0; i < 6; i++) {
				v[i] = cand[iter][i + 1];
				if (v[i] >= k) v[i]++;
			}
			vector c(8, false);
			for (int i = 0; i < 7; i++) c[v[i]] = true;
			int p = 0;
			while (c[p]) p++;
			for (int i = 0; i < 7; i++) if (v[i] > p) v[i]--;
			auto it = lower_bound(cand.begin(), cand.end(), v);
			nxt[iter][k] = it - cand.begin();
		}
	}
	for (int p = 7; p < n; p++) {
		vector ndp(cand.size(), 0);
		for (int iter = 0; iter < cand.size(); iter++) {
			for (int k = 0; k <= 7; k++) {
				int acc = dp[iter];
				for (int i = 0; i < 7; i++) {
					if (cand[iter][i] < k) {
						if (a[p - 7 + i] < 7 - i) continue;
						acc += b[p - 7 + i];
					}
					else {
						if (a[p] < 7 - i) continue;
						acc += b[p];
					}
				}
				ndp[nxt[iter][k]] = max(ndp[nxt[iter][k]], acc);
			}
		}
		dp.swap(ndp);
	}
	return *max_element(dp.begin(), dp.end());
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector a(n, 0), b(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];
	cout << sol(n, a, b) << '\n';
}