#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, i64 k, auto v) {
	sort(v.begin(), v.end(), greater{});
	i64 acc = 0;
	int pos = n - m;
	while (acc < k && pos < n) {
		acc += v[pos];
		pos++;
	}
	if (acc < k) return -1;
	return pos;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	i64 k; cin >> k;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, k, v) << '\n';
}