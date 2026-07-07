#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 1'000'000'007;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int sub(int a, int b) {
	return a < b ? a - b + mod : a - b;
}

auto calc = [](i64 k, string s) {
	int c2 = 0, c3 = 0, c5 = 0, c7 = 0;
	while (k % 2 == 0) k /= 2, c2++;
	while (k % 3 == 0) k /= 3, c3++;
	while (k % 5 == 0) k /= 5, c5++;
	while (k % 7 == 0) k /= 7, c7++;
	vector dp(s.size(), vector(c2 + 1, vector(c3 + 1, vector(c5 + 1, vector(c7 + 1, vector(8, -1))))));
	auto rec = [&](const auto& self, int i, int v2, int v3, int v5, int v7, int f0, int f1, int f2) -> int {
		if (v2 > c2) v2 = c2;
		if (v3 > c3) v3 = c3;
		if (v5 > c5) v5 = c5;
		if (v7 > c7) v7 = c7;
		if (i == s.size()) return f0 || (k == 1 && v2 == c2 && v3 == c3 && v5 == c5 && v7 == c7);
		int& ret = dp[i][v2][v3][v5][v7][f0 * 4 + f1 * 2 + f2];
		if (ret != -1) return ret;
		ret = self(self, i + 1, v2, v3, v5, v7, f0 || f1, f1, f2 || 0 < s[i] - 48);
		for (int x = 1; x <= 9; x++) {
			if (f2 == 0 && x > s[i] - 48) break;
			int val = x;
			int nv2 = v2, nv3 = v3, nv5 = v5, nv7 = v7;
			while (val % 2 == 0) val /= 2, nv2++;
			while (val % 3 == 0) val /= 3, nv3++;
			while (val % 5 == 0) val /= 5, nv5++;
			while (val % 7 == 0) val /= 7, nv7++;
			ret = add(ret, self(self, i + 1, nv2, nv3, nv5, nv7, f0, 1, f2 || x < s[i] - 48));
		}
		return ret;
	};
	return rec(rec, 0, 0, 0, 0, 0, 0, 0, 0);
};

auto sol = [](i64 k, string l, string r) {
	int ret = sub(calc(k, r), calc(k, l));
	i64 acc = 1;
	for (char c : l) acc = acc * ((c - 48) % 10) % k;
	if (acc == 0) ret = add(ret, 1);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	i64 k; cin >> k;
	string l, r; cin >> l >> r;
	cout << sol(k, l, r) << '\n';
}