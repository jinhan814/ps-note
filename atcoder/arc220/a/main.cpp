#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n) {
	deque dq(0, 0);
	if (n % 3 == 1) dq = deque{ 1 };
	else if (n % 3 == 0) dq = deque{ 2, 2, 2, 3, 3, 6 };
	else dq = deque{ 2, 2, 3, 3, 3, 3, 6, 6 };
	if (n < dq.size()) return deque(0, 0);
	while (n > dq.size()) {
		int x = dq.front();
		dq.pop_front();
		dq.push_back(2 * x);
		dq.push_back(2 * x);
		dq.push_back(2 * x);
		dq.push_back(2 * x);
	}
	return dq;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		auto res = sol(n);
		if (res.size()) {
			cout << "Yes" << '\n';
			for (int i = 0; i < n; i++) cout << res[i] << ' ';
			cout << '\n';
		}
		else {
			cout << "No" << '\n';
		}
	}
}