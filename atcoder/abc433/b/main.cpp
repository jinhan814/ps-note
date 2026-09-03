#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector ret(n + 1, -1);
	for (int i = 1; i <= n; i++) {
		for (int j = i - 1; j >= 1; j--) {
			if (v[i] >= v[j]) continue;
			ret[i] = j;
			break;
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];
	auto res = sol(n, v);
	for (int i = 1; i <= n; i++) cout << res[i] << '\n';
}