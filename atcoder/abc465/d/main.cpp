#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](i64 a, i64 b, i64 k) {
	int ret = 0;
	while (a != b) {
		if (a < b) swap(a, b);
		a /= k;
		ret++;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		i64 a, b, k; cin >> a >> b >> k;
		cout << sol(a, b, k) << '\n';
	}
}