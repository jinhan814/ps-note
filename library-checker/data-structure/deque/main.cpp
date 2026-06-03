#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int q; cin >> q;
	deque dq(0, 0);
	while (q--) {
		int op; cin >> op;
		if (op == 0) {
			int x; cin >> x;
			dq.push_front(x);
		}
		else if (op == 1) {
			int x; cin >> x;
			dq.push_back(x);
		}
		else if (op == 2) {
			dq.pop_front();
		}
		else if (op == 3) {
			dq.pop_back();
		}
		else {
			int x; cin >> x;
			cout << dq[x] << '\n';
		}
	}
}