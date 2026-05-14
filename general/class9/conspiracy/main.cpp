#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto g) {
	vector deg(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (!g[i][j]) continue;
			deg[i]++;
		}
	}
	vector buc(n, 0);
	iota(buc.begin(), buc.end(), 1);
	sort(buc.begin(), buc.end(), [&](int i, int j) {
		return deg[i] > deg[j];
	});
	vector c(n + 1, false);
	int sz = 0;
	for (int iter = 0; iter < n; iter++) {
		int i = buc[iter];
		int cnt = 0;
		for (int j = 1; j <= n; j++) {
			if (!g[i][j]) continue;
			if (!c[j]) continue;
			cnt++;
		}
		if (cnt != iter) break;
		c[i] = true;
		sz++;
	}
	vector cnt(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (!g[i][j]) continue;
			if (!c[i] && !c[j]) return 0;
			if (c[i] != c[j]) cnt[i]++;
		}
	}
	if (sz == 1 || sz == n) return n;
	int ret = 1;
	for (int i = 1; i <= n; i++) {
		if (c[i]) {
			if (cnt[i] != 0) continue;
			ret++;
		}
		else {
			if (cnt[i] != sz - 1) continue;
			int p = 1;
			while (!c[p] || g[i][p]) p++;
			if (cnt[p] != 0) continue;
			ret++;
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector g(n + 1, vector(n + 1, false));
	for (int i = 1; i <= n; i++) {
		int k; cin >> k;
		while (k--) {
			int x; cin >> x;
			g[i][x] = true;
		}
	}
	cout << sol(n, g) << '\n';
}