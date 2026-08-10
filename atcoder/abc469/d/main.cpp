#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	int ret = 0;
	for (int x : v[0]) {
		vector buc(0, array{ 0, 0 });
		for (int i = 1; i < m; i++) {
			if (v[i][0] == x || v[i][1] == x) continue;
			buc.push_back(v[i]);
		}
		if (buc.empty()) {
			ret += n - 1;
		}
		else {
			auto f = [&](int x) {
				for (auto [a, b] : buc) {
					if (a == x || b == x) continue;
					return false;
				}
				return true;
			};
			if (f(buc[0][0])) ret++;
			if (f(buc[0][1])) ret++;
		}
	}
	bool flag = true;
	for (int i = 1; i < m; i++) {
		if (v[i][0] == v[0][0] || v[i][1] == v[0][0]) continue;
		if (v[i][0] == v[0][1] || v[i][1] == v[0][1]) continue;
		flag = false;
		break;
	}
	if (flag) ret--;
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(m, array{ 0, 0 });
	for (auto& [a, b] : v) cin >> a >> b;
	cout << sol(n, m, v) << '\n';
}