#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto p, auto v) {
	auto rec = [&](const auto& self, int l, int r) -> vector<i64> {
		if (l > r) return vector(1, i64(0));
		int pos = l;
		for (int i = l; i <= r; i++) {
			if (p[pos] <= p[i]) continue;
			pos = i;
		}
		vector ret(r - l + 2, i64(1) << 60);
		ret[0] = 0;
		auto res_l = self(self, l, pos - 1);
		auto res_r = self(self, pos + 1, r);
		for (int i = 0; i < res_l.size(); i++) {
			for (int j = 0; j < res_r.size(); j++) {
				i64 val = res_l[i] + res_r[j] + v[pos];
				ret[i + j + 1] = min(ret[i + j + 1], val);
			}
		}
		for (int i = 0; i < res_r.size(); i++) {
			ret[i] = min(ret[i], res_r[i]);
		}
		for (int i = 0; i < res_l.size(); i++) {
			ret[i] = min(ret[i], res_l[i]);
		}
		return ret;
	};
	return rec(rec, 1, n);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		vector p(n + 1, 0), v(n + 1, 0);
		for (int i = 1; i <= n; i++) cin >> p[i];
		for (int i = 1; i <= n; i++) cin >> v[i];
		auto res = sol(n, p, v);
		for (int i = 1; i <= n; i++) cout << res[i] << ' ';
		cout << '\n';
	}
}