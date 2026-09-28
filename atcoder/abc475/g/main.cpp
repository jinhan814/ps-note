#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](i64 n, i64 m) {
	auto f = [&](i64 n, auto cand) {
		auto rec = [&](const auto& self, int dep, int lim, int cnt, i64 x) {
			if (dep == cand.size()) return pair(cnt, x);
			pair ret(1, i64(1));
			for (int i = 0; i <= lim; i++) {
				ret = max(ret, self(self, dep + 1, i, cnt * (i + 1), x));
				if (x > n / cand[dep]) break;
				x *= cand[dep];
			}
			return ret;
		};
		return rec(rec, 0, 100, 1, 1);
	};
	vector cand{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47 };
	pair ret(1, i64(1));
	for (int p : cand) {
		int cnt = 0;
		while (m % p == 0) m /= p, cnt++;
		auto c = cand;
		c.erase(lower_bound(c.begin(), c.end(), p));
		i64 acc = 1;
		for (int i = 0; i < cnt && acc <= n; i++) {
			auto res = f(n / acc, c);
			res.first *= i + 1;
			res.second *= acc;
			ret = max(ret, res);
			acc *= p;
		}
	}
	if (m > 1) ret = max(ret, f(n, cand));
	return ret.second;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		i64 n, m; cin >> n >> m;
		cout << sol(n, m) << '\n';
	}
}