#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, auto v) {
	vector buc(1, array{ 0, 0, n, m });
	for (auto [op, v1, v2] : v) {
		vector nbuc(0, array{ 0, 0, 0, 0 });
		for (auto [x, y, a, b] : buc) {
			if (op == 1) {
				int val = min(max(v1 - x, 0), a);
				if (val > 0) nbuc.push_back(array{ x, y - v2, val, b });
				if (val < a) nbuc.push_back(array{ max(x, v1), y + v2, a - val, b });
			}
			else {
				int val = min(max(v1 - y, 0), b);
				if (val > 0) nbuc.push_back(array{ x - v2, y, a, val });
				if (val < b) nbuc.push_back(array{ x + v2, max(y, v1), a, b - val });
			}
		}
		buc.swap(nbuc);
	}
	auto f = [](auto v1, auto v2) {
		auto [x1, y1, a1, b1] = v1;
		auto [x2, y2, a2, b2] = v2;
		bool f1 = max(x1, x2) < min(x1 + a1, x2 + a2);
		bool f2 = max(y1, y2) < min(y1 + b1, y2 + b2);
		if ((x1 == x2 + a2 || x2 == x1 + a1) && f2) return true;
		if ((y1 == y2 + b2 || y2 == y1 + b1) && f1) return true;
		return false;
	};
	vector ret(0, i64(0));
	vector c(buc.size(), false);
	for (int i = 0; i < buc.size(); i++) {
		if (c[i]) continue;
		vector q(1, i);
		c[i] = true;
		i64 acc = 0;
		while (q.size()) {
			int cur = q.back(); q.pop_back();
			acc += i64(buc[cur][2]) * buc[cur][3];
			for (int nxt = 0; nxt < buc.size(); nxt++) {
				if (c[nxt]) continue;
				if (!f(buc[cur], buc[nxt])) continue;
				q.push_back(nxt);
				c[nxt] = true;
			}
		}
		ret.push_back(acc);
	}
	sort(ret.begin(), ret.end());
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int k, n, m; cin >> k >> n >> m;
	vector v(k, array{ 0, 0, 0 });
	for (auto& [op, v1, v2] : v) {
		char c; cin >> c >> v1 >> v2;
		op = c == 'X' ? 1 : 2;
	}
	auto res = sol(n, m, v);
	cout << res.size() << '\n';
	for (i64 x : res) cout << x << ' ';
	cout << '\n';
}