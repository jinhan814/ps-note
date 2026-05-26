#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto calc = [](int n, int x) {
	int ret = 0;
	if (n % 2 == 0) ret += min(x + 1, n + 1);
	if (x > n) ret += (x - n + n % 2) / 2;
	return ret;
};

auto sol = [](int a, int b, int c, int d) {
	i64 ret = 0;
	for (int i = a; i <= b; i++) {
		if (d < 0) {
			ret += calc(abs(i), -c);
			ret -= calc(abs(i), -d - 1);
		}
		else if (c > 0) {
			ret += calc(abs(i), d);
			ret -= calc(abs(i), c - 1);
		}
		else {
			ret += calc(abs(i), -c);
			ret += calc(abs(i), d);
			ret -= calc(abs(i), 0);
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int a, b, c, d; cin >> a >> b >> c >> d;
	cout << sol(a, b, c, d) << '\n';
}