#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, int k, auto v) {
	auto f = [&](int i) {
		i64 ret = 0;
		for (; i >= 0; i -= m) ret += 2 * v[i];
		return ret;
	};
	auto g = [&](int i) {
		i64 ret = 0;
		for (; i < n; i += m) ret += 2 * (k - v[i]);
		return ret;
	};
	int p = lower_bound(v.begin(), v.end(), (k + 1) / 2) - v.begin();
	i64 ret = f(p - 1) + g(p);
	for (int i = p; i <= p + m - 2; i++) {
		ret = min(ret, f(i - m) + k + g(i + 1));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, k, v) << '\n';
}