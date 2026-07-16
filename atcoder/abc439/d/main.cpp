#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto v) {
	i64 ret = 0;
	for (int iter = 0; iter < 2; iter++) {
		map cnt{ pair(0, 0) };
		for (int i = 0; i < n; i++) {
			cnt[v[i]]++;
			if (v[i] % 5 != 0) continue;
			int x = v[i] / 5;
			ret += i64(cnt[3 * x]) * cnt[7 * x];
		}
		reverse(v.begin(), v.end());
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