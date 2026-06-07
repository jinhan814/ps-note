#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, int k, auto v) {
	vector buc(n + 1, vector(0, 0));
	for (auto [a, b] : v) buc[a].push_back(b);
	vector c1(0, 0), c2(0, 0);
	for (int i = 1; i <= n; i++) {
		if (buc[i].empty()) continue;
		sort(buc[i].begin(), buc[i].end());
		c1.push_back(buc[i].back());
		buc[i].pop_back();
		for (int x : buc[i]) c2.push_back(x);
	}
	sort(c1.begin(), c1.end(), greater{});
	i64 ret = 0;
	for (int i = 0; i < k; i++) ret += c1[i];
	for (int i = k; i < c1.size(); i++) c2.push_back(c1[i]);
	sort(c2.begin(), c2.end(), greater{});
	for (int i = 0; i < m - k; i++) ret += c2[i];
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(n, array{ 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i][0] >> v[i][1];
	cout << sol(n, m, k, v) << '\n';
}