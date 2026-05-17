#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	priority_queue<int> pq1;
	priority_queue<int, vector<int>, greater<>> pq2;
	auto push = [&](int x) {
		if (pq1.size() == pq2.size()) pq1.push(x);
		else pq2.push(x);
		while (pq1.size() && pq2.size() && pq1.top() > pq2.top()) {
			int v1 = pq1.top();
			int v2 = pq2.top();
			pq1.pop();
			pq2.pop();
			pq1.push(v2);
			pq2.push(v1);
		}
	};
	int x; cin >> x;
	push(x);
	int q; cin >> q;
	while (q--) {
		int a, b; cin >> a >> b;
		push(a);
		push(b);
		cout << pq1.top() << '\n';
	}
}