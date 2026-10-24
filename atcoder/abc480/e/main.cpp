#include <bits/stdc++.h>
using namespace std;

using i128 = __int128;
using i64 = long long;

auto sol = [](i64 n) {
	i64 ret = 0;
	for (int i = 1; i <= 1'000'000; i++) {
		int lo = 0, hi = 1 << 30;
		while (lo + 1 < hi) {
			int mid = (lo + hi) / 2;
			i128 val = i128(i) * (i + mid) * (i + 2 * mid);
			if (val <= n) lo = mid;
			else hi = mid;
		}
		ret += lo;
	}
	for (int k = 4; k <= 19; k++) {
		int x = 1'000'000;
		for (int i = 1; x > 0; i++) {
			while (x > 0) {
				i128 val = 1;
				for (int j = 0; j < k && val <= n; j++) val *= i + x * j;
				if (val <= n) break;
				x--;
			}
			ret += x;
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	i64 n; cin >> n;
	cout << sol(n) << '\n';
}