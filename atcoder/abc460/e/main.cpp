#include <bits/stdc++.h>
using namespace std;

using i128 = __int128;
using i64 = long long;

constexpr int mod = 998'244'353;

auto sol = [](i64 n, int m) {
	vector p(1, i128(1));
	vector c(1, i64(0));
	while (p.back() <= n) {
		i128 x = p.back();
		p.push_back(x * 10);
		c.push_back(min(x * 10 - 1, i128(n)) - x + 1);
	}
	int ret = 0;
	for (int i = 1; i < p.size(); i++) {
		if ((p[i] - 1) % m == 0) {
			ret += (n % mod) * (c[i] % mod) % mod;
			if (ret >= mod) ret -= mod;
		}
		else {
			int v1 = (p[i] - 1) % m;
			int v2 = gcd(v1, m);
			i64 v3 = n / (m / v2);
			ret += (v3 % mod) * (c[i] % mod) % mod;
			if (ret >= mod) ret -= mod;
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		i64 n; cin >> n;
		int m; cin >> m;
		cout << sol(n, m) << '\n';
	}
}