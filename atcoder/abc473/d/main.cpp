#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector v(0, 0);
	vector buc(k + 1, vector(0, vector(0, 0)));
	auto rec = [&](const auto& self, int i, int val) {
		if (i == n + 1) {
			buc[val].push_back(v);
			return;
		}
		for (int x = 0; i * x <= val; x++) {
			v.push_back(x);
			self(self, i + 1, val - i * x);
			v.pop_back();
		}
	};
	rec(rec, 2, k);
	for (int i = 0; i <= k; i++) {
		for (auto v : buc[i]) {
			cout << i;
			for (int x : v) cout << ' ' << x;
			cout << '\n';
		}
	}
}