#include <bits/stdc++.h>
using namespace std;

using i128 = __int128;
using i64 = long long;

auto sol = [](i64 n) {
	i64 ret = 0;
	for (int x = 1; i64(x) * (x + 1) * (x + 2) <= n; x++) {
		for (int k = 3; ; k++) {
			int lo = 0, hi = 1 << 30;
			while (lo + 1 < hi) {
				int mid = (lo + hi) / 2;
				i128 val = 1;
				for (int i = 0; i < k && val <= n; i++) val *= x + i * mid;
				if (val <= n) lo = mid;
				else hi = mid;
			}
			if (lo == 0) break;
			ret += lo;
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	i64 n; cin >> n;
	cout << sol(n) << '\n';
}