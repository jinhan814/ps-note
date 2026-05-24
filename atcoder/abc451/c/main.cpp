#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int q; cin >> q;
	priority_queue<int, vector<int>, greater<>> pq;
	while (q--) {
		int op, x; cin >> op >> x;
		if (op == 1) {
			pq.push(x);
		}
		else {
			while (pq.size() && pq.top() <= x) {
				pq.pop();
			}
		}
		cout << pq.size() << '\n';
	}
}