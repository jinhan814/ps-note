#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 998'244'353;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int sub(int a, int b) {
	return a < b ? a - b + mod : a - b;
}

constexpr int mul(int a, int b) {
	return i64(a) * b % mod;
}

auto sol = [](int n, int m, auto a, auto b) {
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	vector p(n + 1, 0);
	for (int i = 0; i < n; i++) p[i + 1] = add(p[i], a[i]);
	int ret = 0;
	for (int x : b) {
		int i = lower_bound(a.begin(), a.end(), x) - a.begin();
		ret = add(ret, sub(mul(i, x), p[i]));
		ret = add(ret, sub(sub(p[n], p[i]), mul(n - i, x)));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector a(n, 0), b(m, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < m; i++) cin >> b[i];
	cout << sol(n, m, a, b) << '\n';
}