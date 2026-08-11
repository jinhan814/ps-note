#include <bits/stdc++.h>
using namespace std;

using f64 = double;

auto sol = [](int n, int k, string s) {
	vector p(n + 1, 0);
	for (int i = 0; i < n; i++) {
		p[i + 1] = p[i];
		if (s[i] == 'o') p[i + 1]++;
	}
	vector pos(n + 1, -1);
	for (int i = 1, j = 1; i <= n; i++) {
		while (j + 1 <= i && p[i] - p[j] >= k) j--;
		if (p[i] - p[j - 1] >= k) pos[i] = j;
	}
	double lo = 0, hi = 1;
	for (int iter = 0; iter < 100; iter++) {
		double mid = (lo + hi) / 2;
		double mn = 1e9;
		bool flag = false;
		for (int i = 1, j = 0; i <= n; i++) {
			while (j < i && p[i] - p[j] >= k) mn = min(mn, p[j] - mid * j), j++;
			if (p[i] - mid * i < mn) continue;
			flag = true;
			break;
		}
		if (flag) lo = mid;
		else hi = mid;
	}
	return lo;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	string s; cin >> s;
	cout << fixed << setprecision(20);
	cout << sol(n, k, s) << '\n';
}