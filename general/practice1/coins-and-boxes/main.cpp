#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto a, auto b) {
	vector buc(1, 0);
	for (int i = 0, j = 0; i < n && j < n;) {
		if (a[i] <= b[j]) i++;
		else j++;
		if (i == j) buc.push_back(i);
	}
	buc.push_back(n);
	i64 ret = i64(1) << 60;
	i64 acc = 0;
	for (int i = 1; i < buc.size(); i++) {
		int l = buc[i - 1];
		int r = buc[i] - 1;
		int v1 = min(a[l], b[l]);
		int v2 = max(a[r], b[r]);
		acc += v1 - (l > 0 ? max(a[l - 1], b[l - 1]) : 0);
		ret = min(ret, acc + 2 * max(a[n - 1], b[n - 1]) - v1 - a[l]);
		acc += i64(v2 - v1) * (a[l] < b[l] ? 3 : 1);
	}
	ret = min(ret, acc);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector a(n, 0), b(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];
	cout << sol(n, a, b) << '\n';
}