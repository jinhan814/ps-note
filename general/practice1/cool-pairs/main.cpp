#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, i64 k, auto a, auto b) {
	vector ret(n + 1, array{ 0, 0 });
	int i = 1;
	while (k > n - a[i]) {
		ret[a[i]][0] = -n;
		k -= n - a[i];
		i++;
	}
	ret[a[i]][0] = -1;
	int j = n, rem = n - a[i] - k;
	while (rem > 0) {
		ret[b[j]][1] = 1;
		if (a[i] < b[j]) rem--;
		j--;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	i64 k; cin >> k;
	vector a(n + 1, 0), b(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	auto res = sol(n, k, a, b);
	cout << "Yes" << '\n';
	for (int i = 1; i <= n; i++) cout << res[i][0] << ' ';
	cout << '\n';
	for (int i = 1; i <= n; i++) cout << res[i][1] << ' ';
	cout << '\n';
}