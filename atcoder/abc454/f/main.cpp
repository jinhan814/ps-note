#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto calc = [](int n, int m, auto v) {
	v.push_back(0);
	for (int i = n; i >= 1; i--) {
		v[i] -= v[i - 1];
		if (v[i] < 0) v[i] += m;
	}
	i64 acc = 0;
	for (int i = 0; i <= n; i++) {
		acc += v[i];
	}
	assert(acc % m == 0);
	int k = acc / m;
	sort(v.begin(), v.end(), greater{});
	i64 ret = 0;
	for (int i = 0; i < k; i++) {
		ret += m - v[i];
	}
	return ret;
};

auto sol = [](int n, int m, auto v) {
	if (n == 1) return i64(0);
	if (m == 1) return i64(0);
	vector c(n / 2, 0);
	for (int i = 0; i < n - 1 - i; i++) {
		int j = n - 1 - i;
		if (v[i] < v[j]) c[i] = m - v[j] + v[i];
		if (v[i] > v[j]) c[i] = v[i] - v[j];
	}
	return calc(n / 2, m, c);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n, m; cin >> n >> m;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << sol(n, m, v) << '\n';
	}
}