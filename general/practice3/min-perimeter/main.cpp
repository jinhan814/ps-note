#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using f64 = double;

auto sol = [](int n, auto v) {
	sort(v.begin(), v.end());
	auto f = [&](int i, int j) {
		i64 dx = v[i][0] - v[j][0];
		i64 dy = v[i][1] - v[j][1];
		return sqrt(dx * dx + dy * dy);
	};
	auto rec = [&](const auto& self, int l, int r) -> f64 {
		if (r - l + 1 < 3) return 1e18;
		int mid = (l + r) / 2;
		f64 ret = min(self(self, l, mid), self(self, mid + 1, r));
		vector c(0, 0);
		for (int i = l; i <= r; i++) {
			if (abs(v[mid][0] - v[i][0]) >= ret / 2) continue;
			c.push_back(i);
		}
		sort(c.begin(), c.end(), [&](int i, int j) { return v[i][1] < v[j][1]; });
		for (int i = 0; i < c.size(); i++) {
			for (int j = i + 1; j < c.size(); j++) {
				if (v[c[j]][1] - v[c[i]][1] >= ret / 2) break;
				for (int k = j + 1; k < c.size(); k++) {
					if (v[c[k]][1] - v[c[i]][1] >= ret / 2) break;
					f64 val = f(c[i], c[j]) + f(c[i], c[k]) + f(c[j], c[k]);
					ret = min(ret, val);
				}
			}
		}
		return ret;
	};
	return rec(rec, 0, n - 1);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int iter = 1; iter <= tc; iter++) {
		int n; cin >> n;
		vector v(n, array{ 0, 0 });
		for (auto& [a, b] : v) cin >> a >> b;
		cout << fixed << setprecision(20);
		cout << "Case #" << iter << ": ";
		cout << sol(n, v) << '\n';
	}
}