#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto a, auto b) {
	deque dq(0, pair(0, 0));
	for (int i = 0; i < n; i++) {
		dq.push_back(pair(i, a[i]));
		int x = b[i];
		while (x > 0) {
			int val = min(x, dq.front().second);
			x -= val;
			dq.front().second -= val;
			if (dq.front().second == 0) dq.pop_front();
		}
		if (dq.size() && i - dq.front().first + 1 >= m) {
			dq.pop_front();
		}
	}
	int ret = 0;
	for (auto [_, x] : dq) ret += x;
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n, m; cin >> n >> m;
		vector a(n, 0), b(n, 0);
		for (int i = 0; i < n; i++) cin >> a[i];
		for (int i = 0; i < n; i++) cin >> b[i];
		cout << sol(n, m, a, b) << '\n';
	}
}