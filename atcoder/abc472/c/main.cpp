#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, i64 k, auto v) {
	vector ret(n, false);
	i64 acc = 0;
	deque dq(0, 0);
	for (int i = 0; i < n; i++) {
		while (dq.size() && dq.front() <= i - m) {
			acc -= v[dq.front()];
			dq.pop_front();
		}
		if (acc + v[i] > k) continue;
		ret[i] = true;
		acc += v[i];
		dq.push_back(i);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	i64 k; cin >> k;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	auto res = sol(n, m, k, v);
	for (int i = 0; i < n; i++) cout << (res[i] ? "Yes" : "No") << '\n';
}