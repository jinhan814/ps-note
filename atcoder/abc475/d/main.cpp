#include <bits/stdc++.h>
using namespace std;

auto is_prime = [](int n) {
	if (n < 2) return false;
	for (int i = 2; i * i <= n; i++) {
		if (n % i) continue;
		return false;
	}
	return true;
};

auto sol = [](string s) {
	vector v(26, -1);
	auto rec = [&](const auto& self, int p, int mask) -> int {
		if (p == s.size()) {
			int val = 0;
			for (char c : s) val = 10 * val + v[c - 'a'];
			if (is_prime(val)) return val;
			return -1;
		}
		else {
			if (v[s[p] - 'a'] != -1) return self(self, p + 1, mask);
			for (int x = 0; x <= 9; x++) {
				if (p == 0 && x == 0) continue;
				if (mask >> x & 1) continue;
				v[s[p] - 'a'] = x;
				int res = self(self, p + 1, mask | 1 << x);
				if (res != -1) return res;
				v[s[p] - 'a'] = -1;
			}
			return -1;
		}
	};
	return rec(rec, 0, 0);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	cout << sol(s) << '\n';
}