#include <bits/stdc++.h>
using namespace std;

auto sol = [](int a, int b) {
	auto rec = [&](const auto& self, int l, int r, int k) -> int {
		int sz = (1 << k) - 1;
		int ret = -1;
		if (l <= sz && r <= 2 * sz - 1) {
			int res = self(self, l, min(r, sz), k - 1);
			ret = max(ret, res);
		}
		if (l <= 2 * sz && r >= sz + 1) {
			int res = self(self, max(l, sz + 1) - sz, min(r, 2 * sz) - sz, k - 1);
			ret = max(ret, res + k);
		}
		if (r == 2 * sz + 1) {
			ret = max(ret, k + 1);
		}
		return ret;
	};
	return rec(rec, a, b, 29);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int a, b; cin >> a >> b;
		cout << sol(a, b) << '\n';
	}
}