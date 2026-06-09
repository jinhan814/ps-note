#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 998'244'353;

auto sol = [](int n, auto v) {
	int p = 0;
	while (p + 1 <= n && v[p + 1] == p + 1) p++;
	if (p == n) return i64(n) * (n - 1) / 2 + 1;
	return i64(p) * (2 * n - p - 1) / 2;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		vector v(n + 1, 0);
		for (int i = 1; i <= n; i++) cin >> v[i];
		cout << sol(n, v) % mod << '\n';
	}
}