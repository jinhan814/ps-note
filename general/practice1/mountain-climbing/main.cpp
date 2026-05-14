#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto a, auto b) {
	vector p(n, 0);
	iota(p.begin(), p.end(), 0);
	sort(p.begin(), p.end(), [&](int i, int j) {
		bool f1 = a[i] <= b[i];
		bool f2 = a[j] <= b[j];
		if (f1 != f2) return f1;
		if (f1) return a[i] < a[j];
		return b[i] > b[j];
	});
	int ret = 0, acc = 0;
	for (int i : p) {
		acc += a[i];
		ret = max(ret, acc);
		acc -= b[i];
	}
	for (int i = 0; i < n; i++) {
		ret += b[i];
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector a(n, 0), b(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
	cout << sol(n, a, b) << '\n';
}