#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	multiset s{ 0 }; s.clear();
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		s.insert(x);
	}
	while (q--) {
		int op; cin >> op;
		if (op == 0) {
			int x; cin >> x;
			s.insert(x);
		}
		else if (op == 1) {
			cout << *s.begin() << '\n';
			s.erase(s.begin());
		}
		else {
			cout << *prev(s.end()) << '\n';
			s.erase(prev(s.end()));
		}
	}
}