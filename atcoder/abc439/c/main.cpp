#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n) {
	vector c(n + 1, 0);
	for (int i = 1; i * i <= n; i++) {
		for (int j = i + 1; ; j++) {
			int x = i * i + j * j;
			if (x > n) break;
			c[x]++;
		}
	}
	vector ret(0, 0);
	for (int i = 1; i <= n; i++) {
		if (c[i] != 1) continue;
		ret.push_back(i);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	auto res = sol(n);
	cout << res.size() << '\n';
	for (int x : res) cout << x << ' ';
	cout << '\n';
}