#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto calc = [](auto v, int k) {
	vector p(v.size() + 1, 0);
	for (int i = 0; i < v.size(); i++) p[i + 1] = p[i] + v[i];
	int ret = 0;
	for (int i = 0, p1 = 0, p2 = 0; i < v.size(); i++) {
		if (p1 < i) p1 = i;
		if (p2 < i) p2 = i;
		while (p1 < v.size() && p[p1 + 1] - p[i] <= k) p1++;
		while (p2 < v.size() && p[p2 + 1] - p[i] <= k - 1) p2++;
		ret += p1 - p2;
	}
	return ret;
};

auto sol = [](int n, int m, int k, auto v) {
	i64 ret = 0;
	for (int l = 0; l < m; l++) {
		vector c(n, 0);
		for (int r = l; r < m; r++) {
			for (int i = 0; i < n; i++) {
				if (v[i][r] == '0') continue;
				c[i]++;
			}
			ret += calc(c, k);
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, k, v) << '\n';
}