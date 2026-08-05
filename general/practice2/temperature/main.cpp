#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	int ret = 0;
	int cnt = 0;
	deque q(0, pair(0, 0));
	for (auto [l, r] : v) {
		int acc = 1;
		while (q.size() && q.front().first <= l) {
			acc += q.front().second;
			q.pop_front();
		}
		while (q.size() && q.back().first > r) {
			cnt -= q.back().second;
			q.pop_back();
		}
		q.push_front(pair(l, acc));
		cnt++;
		ret = max(ret, cnt);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0 });
	for (auto& [a, b] : v) cin >> a >> b;
	cout << sol(n, v) << '\n';
}