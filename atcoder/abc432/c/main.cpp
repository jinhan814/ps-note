#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int a, int b, auto v) {
	int val = i64(a) * v[0] % (b - a);
	int mn = 1 << 30;
	for (int i = 0; i < n; i++) {
		if (val != i64(a) * v[i] % (b - a)) return i64(-1);
		mn = min(mn, v[i]);
	}
	i64 k = (i64(b) * mn - val) / (b - a) * (b - a) + val;
	i64 ret = 0;
	for (int i = 0; i < n; i++) {
		i64 x = (k - i64(a) * v[i]) / (b - a);
		if (x < 0) return i64(-1);
		ret += x;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, a, b; cin >> n >> a >> b;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, a, b, v) << '\n';
}