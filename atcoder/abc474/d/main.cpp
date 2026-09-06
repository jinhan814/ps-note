#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto a, auto b) {
	for (int i = 0; i < n; i++) {
		if (a[i] <= b[i]) continue;
		vector ret(n, i64(1));
		ret[i] = 1e18;
		return ret;
	}
	return vector(0, i64(0));
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector a(n, 0), b(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];
	auto res = sol(n, a, b);
	if (res.size()) {
		cout << "Yes" << '\n';
		for (int i = 0; i < n; i++) cout << res[i] << ' ';
		cout << '\n';
	}
	else {
		cout << "No" << '\n';
	}
}