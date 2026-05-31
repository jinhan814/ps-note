#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int x1, int y1, int r1, int x2, int y2, int r2) {
	i64 l = i64(r1 - r2) * (r1 - r2);
	i64 r = i64(r1 + r2) * (r1 + r2);
	i64 d = i64(x1 - x2) * (x1 - x2) + i64(y1 - y2) * (y1 - y2);
	return l <= d && d <= r;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int x1, y1, r1; cin >> x1 >> y1 >> r1;
		int x2, y2, r2; cin >> x2 >> y2 >> r2;
		cout << (sol(x1, y1, r1, x2, y2, r2) ? "Yes" : "No") << '\n';
	}
}