#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	vector ret(0, 0);
	for (int i = 1; i <= n; i++) {
		bool flag = true;
		for (int j = 1; j <= n; j++) {
			if (i == j) continue;
			if (abs(v[i] - v[j]) >= m) continue;
			flag = false;
			break;
		}
		if (flag) ret.push_back(i);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];
	auto res = sol(n, m, v);
	cout << res.size() << '\n';
	for (int x : res) cout << x << ' ';
	cout << '\n';
}