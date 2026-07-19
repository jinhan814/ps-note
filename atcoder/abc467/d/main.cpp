#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](auto v) {
	i64 x1 = v[1][0] - v[0][0];
	i64 y1 = v[1][1] - v[0][1];
	i64 x2 = v[3][0] - v[2][0];
	i64 y2 = v[3][1] - v[2][1];
	if (x1 * y2 != x2 * y1) return true;
	i64 x3 = (v[2][0] + v[3][0]) - (v[0][0] + v[1][0]);
	i64 y3 = (v[2][1] + v[3][1]) - (v[0][1] + v[1][1]);
	if (x1 * x3 + y1 * y3 == 0) return true;
	return false;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		vector v(4, array{ 0, 0 });
		for (auto& [a, b] : v) cin >> a >> b;
		cout << (sol(v) ? "Yes" : "No") << '\n';
	}
}