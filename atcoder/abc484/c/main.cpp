#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto a, auto b) {
	int l = 0, r = n - 1;
	while (l < n && a[l] == b[l]) l++;
	if (l == n) return true;
	while (r >= 0 && a[r] == b[r]) r--;
	bool f1 = a[r] == b[l], f2 = a[l] == b[r];
	for (int i = l; i < r; i++) {
		if (a[i] != b[i + 1]) f1 = false;
		if (a[i + 1] != b[i]) f2 = false;
	}
	return f1 || f2;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector a(n, 0), b(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];
	cout << (sol(n, a, b) ? "Yes" : "No") << '\n';
}