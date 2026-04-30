#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, i64 k) {
	int ret = 0;
	i64 acc = 0;
	while (acc < n * k) {
		i64 val = acc / n + 1;
		ret++;
		acc += val;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int iter = 1; iter <= tc; iter++) {
		int n; cin >> n;
		i64 k; cin >> k;
		cout << "Case #" << iter << ": ";
		cout << sol(n, k) << '\n';
	}
}