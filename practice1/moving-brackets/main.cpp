#include <bits/stdc++.h>
using namespace std;

auto calc = [](int n, string s) {
	vector psum(n + 1, 0);
	vector buc(n / 2 + 1, vector(0, 0));
	buc[0].push_back(0);
	for (int i = 0; i < n; i++) {
		psum[i + 1] = psum[i] + (s[i] == '(' ? 1 : -1);
		buc[psum[i + 1]].push_back(i + 1);
	}
	vector ret(0, pair(0, 0));
	auto rec = [&](const auto& self, int l, int r, int x) -> void {
		auto p = lower_bound(buc[x].begin(), buc[x].end(), l);
		for (; *p != r; p++) {
			auto it = lower_bound(buc[x + 1].begin(), buc[x + 1].end(), *p + 1);
			for (; *it != *next(p) - 1; it++) {
				int a = *it;
				int b = *next(it);
				ret.push_back(pair(a + 1, b));
				self(self, a + 1, b - 1, x + 2);
			}
		}
	};
	rec(rec, 0, n, 0);
	return ret;
};

auto sol = [](int n, string a, string b) {
	auto ra = calc(n, a);
	auto rb = calc(n, b);
	while (rb.size()) ra.push_back(rb.back()), rb.pop_back();
	return ra;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		string a, b; cin >> a >> b;
		auto res = sol(n, a, b);
		cout << res.size() << '\n';
		for (auto [l, r] : res) cout << l << ' ' << r << '\n';
	}
}