#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 998'244'353;

constexpr int mul(int a, int b) {
	return i64(a) * b % mod;
}

auto sol = [](i64 n) {
	if (n == 1) return 1;
	if (n <= 13) return -1;
	int p1 = 1, r1 = 1, p2 = 2, r2 = 2;
	auto f = [&](int k) {
		if (p1 > k) p1 = 1, r1 = 1;
		while (p1 < k) p1 += 2, r1 = mul(r1, p1);
		if (p2 > k) p2 = 2, r2 = 2;
		while (p2 < k) p2 += 2, r2 = mul(r2, p2);
		return k % 2 == 1 ? r1 : r2;
	};
	int ret = 29'030'400;
	for (int i = 15; i <= 18 && i <= n; i++) {
		ret = mul(ret, 2 * i - 25);
	}
	for (int x = 6; ; x++) {
		i64 l = i64(x) * x / 2 + 1;
		i64 r = min(i64(x + 1) * (x + 1) / 2, n);
		if (l > r) break;
		ret = mul(ret, f(2 * (r - l + 1) - (x % 2)));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	i64 n; cin >> n;
	cout << sol(n) << '\n';
}