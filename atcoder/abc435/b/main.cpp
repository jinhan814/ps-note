#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	int ret = 0;
	for (int i = 0; i < n; i++) {
		int acc = 0;
		for (int j = i; j < n; j++) {
			acc += v[j];
			bool flag = true;
			for (int k = i; k <= j; k++) {
				if (acc % v[k] != 0) continue;
				flag = false;
				break;
			}
			if (flag) ret++;
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}