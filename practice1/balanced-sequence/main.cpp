#include <bits/stdc++.h>
using namespace std;

auto calc = [](int n, auto v) {
	sort(v.begin(), v.end(), [](auto a, auto b) {
		int fa = a[0] < a[1] ? 0 : a[0] == a[1] ? 1 : 2;
		int fb = b[0] < b[1] ? 0 : b[0] == b[1] ? 1 : 2;
		if (fa != fb) return fa < fb;
		if (fa <= 1) return a[0] < b[0];
		return a[1] > b[1];
	});
	int ret = 0, a = 0, b = 0;
	for (int i = 0; i < n; i++) {
		int x = min(b, v[i][0]);
		ret += x;
		a = a + v[i][0] - x;
		b = b + v[i][1] - x;
	}
	return ret;
};

auto sol = [](int n, auto v) {
	int ret = 0;
	vector c(n, array{ 0, 0 });
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < v[i].size(); j++) {
			if (v[i][j] == '(') c[i][0]++;
			else if (c[i][0] == 0) c[i][1]++;
			else c[i][0]--, ret++;
		}
	}
	ret += calc(n, c);
	ret *= 2;
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		vector v(n, string{});
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << sol(n, v) << '\n';
	}
}