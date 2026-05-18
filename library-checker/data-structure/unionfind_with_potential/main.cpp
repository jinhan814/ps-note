#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998'244'353;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int sub(int a, int b) {
	return a < b ? a - b + mod : a - b;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector p(n + 1, -1);
	vector v(n + 1, 0);
	auto find = [&](const auto& self, int i) -> int {
		if (p[i] == -1) return i;
		if (p[p[i]] == -1) return p[i];
		self(self, p[i]);
		v[i] = add(v[i], v[p[i]]);
		p[i] = p[p[i]];
		return p[i];
	};
	while (q--) {
		int op; cin >> op;
		if (op == 0) {
			int a, b, c; cin >> a >> b >> c;
			int pa = find(find, a);
			int pb = find(find, b);
			if (pa == pb) {
				cout << (sub(v[b], v[a]) == c) << '\n';
			}
			else {
				v[pb] = add(c, sub(v[a], v[b]));
				p[pb] = pa;
				cout << 1 << '\n';
			}
		}
		else {
			int a, b; cin >> a >> b;
			int pa = find(find, a);
			int pb = find(find, b);
			if (pa == pb) {
				cout << sub(v[b], v[a]) << '\n';
			}
			else {
				cout << -1 << '\n';
			}
		}
	}
}