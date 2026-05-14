#include <bits/stdc++.h>
using namespace std;

auto sol = [](auto v) {
	vector dp(9, vector(9, vector(1 << 13, -1)));
	auto rec = [&](const auto& self, int x, int y, int mask) -> int {
		if (y == 9) x++, y = 0;
		if (x == 9) return mask == 0 ? 0 : 1 << 30;
		int& ret = dp[x][y][mask];
		if (ret != -1) return ret;
		ret = 1 << 30;
		{
			int nmask = mask;
			bool flag = true;
			if (y == 8 && nmask & (1 << 12)) flag = false;
			if (x % 3 == 2 && y == 8 && nmask & (1 << 9 | 1 << 10 | 1 << 11)) flag = false;
			if (flag) ret = min(ret, self(self, x, y + 1, nmask) + (v[x][y] != '0'));
		}
		{
			int nmask = mask;
			nmask ^= 1 << y;
			nmask ^= 1 << (9 + y / 3);
			nmask ^= 1 << 12;
			bool flag = true;
			if (y == 8 && nmask & (1 << 12)) flag = false;
			if (x % 3 == 2 && y == 8 && nmask & (1 << 9 | 1 << 10 | 1 << 11)) flag = false;
			if (flag) ret = min(ret, self(self, x, y + 1, nmask) + (v[x][y] != '1'));
		}
		return ret;
	};
	return rec(rec, 0, 0, 0);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	vector v(9, string(0, 0));
	for (int i = 0; i < 9; i++) cin >> v[i];
	cout << sol(v) << '\n';
}