#include <bits/stdc++.h>
using namespace std;

auto sol = [](int k, int q, auto qs) {
	vector ret(0, 0);
	priority_queue<int> pq;
	int cnt = 0;
	for (auto [op, a, b] : qs) {
		if (op == 1) {
			pq.push(b - a);
		}
		else {
			while (pq.size() && pq.top() + a >= k) pq.pop(), cnt++;
			if (cnt > 0) ret.push_back(k), cnt--;
			else if (pq.size()) ret.push_back(pq.top() + a), pq.pop();
			else ret.push_back(-1);
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int q, k; cin >> q >> k;
	vector qs(q, array{ 0, 0, 0 });
	for (auto& [op, a, b] : qs) {
		cin >> op >> a;
		if (op == 1) cin >> b;
	}
	auto res = sol(k, q, qs);
	for (int x : res) cout << x << '\n';
}