#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n) {
	if (n < 10) return string(1, 48 + n);
	vector d(9 * n, -1);
	vector p(9 * n, pair(-1, -1));
	vector q(0, pair(0, 0));
	for (int i = 1; i <= 9; i++) {
		d[9 * i + (i - 1)] = 0;
		q.push_back(pair(i, i));
	}
	while (q.size()) {
		vector nq(0, pair(0, 0));
		for (auto [a, b] : q) {
			if (a == 0) {
				string ret;
				while (a != -1) {
					ret.push_back(48 + b);
					tie(a, b) = p[9 * a + (b - 1)];
				}
				reverse(ret.begin(), ret.end());
				return ret;
			}
			for (int x = b; x <= 9; x++) {
				int val = (a * 10 + x) % n;
				if (d[9 * val + (x - 1)] != -1) break;
				d[9 * val + (x - 1)] = d[9 * a + (b - 1)] + 1;
				p[9 * val + (x - 1)] = pair(a, b);
				nq.push_back(pair(val, x));
			}
		}
		q.swap(nq);
	}
	return string("-1");
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	cout << sol(n) << '\n';
}