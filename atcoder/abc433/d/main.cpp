#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, auto v) {
	vector buc(11, vector(0, 0));
	for (int x : v) {
		int sz = to_string(x).size();
		buc[sz].push_back(x % m);
	}
	for (int i = 1; i <= 10; i++) {
		sort(buc[i].begin(), buc[i].end());
	}
	i64 ret = 0;
	for (int x : v) {
		for (int i = 1; i <= 10; i++) {
			x = i64(x) * 10 % m;
			int val = x == 0 ? 0 : m - x;
			auto [lo, hi] = equal_range(buc[i].begin(), buc[i].end(), val);
			ret += hi - lo;
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}