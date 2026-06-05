#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto v) {
	i64 ret = 0;
	for (int i = 1; i < n; i++) {
		if (v[i] <= v[i - 1] + 1) continue;
		ret += v[i] - (v[i - 1] + 1);
		v[i] = v[i - 1] + 1;
	}
	for (int i = n - 2; i >= 0; i--) {
		if (v[i] <= v[i + 1] + 1) continue;
		ret += v[i] - (v[i + 1] + 1);
		v[i] = v[i + 1] + 1;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << sol(n, v) << '\n';
	}
}