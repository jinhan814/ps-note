#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	sort(v.begin(), v.end());
	vector ret(0, 0);
	if (v[0] == v[n - 1]) {
		ret.push_back(v[n - 1]);
	}
	else {
		int p = n - 1;
		while (v[p] == v[n - 1]) p--;
		if (p % 2 == 1) {
			bool flag = true;
			for (int i = 0; i <= p; i++) {
				if (v[i] + v[p - i] == v[n - 1]) continue;
				flag = false;
				break;
			}
			if (flag) ret.push_back(v[n - 1]);
		}
	}
	if (n % 2 == 0) {
		bool flag = true;
		for (int i = 0; i < n; i++) {
			if (v[i] + v[n - 1 - i] == v[0] + v[n - 1]) continue;
			flag = false;
			break;
		}
		if (flag) ret.push_back(v[0] + v[n - 1]);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	auto res = sol(n, v);
	for (int x : res) cout << x << ' ';
	cout << '\n';
}