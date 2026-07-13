#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	int ret = 0;
	vector c1(n + 1, false);
	vector c2(n + 1, false);
	for (int i = m - 1; i >= 0; i--) {
		auto [a, b] = v[i];
		if (!c1[a] && !c2[b]) ret++;
		c1[a] = true;
		c2[b] = true;
	}
	return ret;
};

int main() {
	int n, m; cin >> n >> m;
	vector v(m, array{ 0, 0 });
	for (auto& [a, b] : v) cin >> a >> b;
	cout << sol(n, m, v) << '\n';
}