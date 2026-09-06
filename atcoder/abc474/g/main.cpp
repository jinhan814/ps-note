#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int k) {
	if (n % 2 == 0) return string(0, 0);
	if (k % 2 == 1) return string(0, 0);
	if (k < n - 1 || k > (n * n - 1) / 2) return string(0, 0);
	int x = ((n * n - 1) / 2 - k) / 2;
	int q = x / ((n - 1) / 2);
	int r = x % ((n - 1) / 2);
	string ret;
	for (int i = 0; i < q; i++) {
		ret += string(n - 1, 'D');
		ret += 'R';
		ret += string(n - 1, 'U');
		ret += 'R';
	}
	if (r == 0) {
		for (int i = 0; i <= n - 1; i++) {
			if (i > 0) ret += 'D';
			ret += string(n - 2 * q - 1, "RL"[i % 2]);
		}
	}
	else {
		ret += string(2 * r, 'D');
		ret += 'R';
		ret += string(2 * r, 'U');
		ret += 'R';
		for (int i = 0; i <= 2 * r; i++) {
			if (i > 0) ret += 'D';
			ret += string(n - 2 * q - 3, "RL"[i % 2]);
		}
		for (int i = 2 * r + 1; i <= n - 1; i++) {
			ret += 'D';
			ret += string(n - 2 * q - 1, "RL"[i % 2]);
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n, k; cin >> n >> k;
		string res = sol(n, k);
		if (res.size()) {
			cout << "Yes" << '\n';
			cout << res << '\n';
		}
		else {
			cout << "No" << '\n';
		}
	}
}