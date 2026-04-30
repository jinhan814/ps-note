#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	vector c1(1'000'001, i64(0)); c1[1] = 1;
	map c2{ pair(1, i64(1)) };
	auto rec = [&](const auto& self, int n) -> i64 {
		i64 ret = n <= 1'000'000 ? c1[n] : c2[n];
		if (ret) return ret;
		int i = 2;
		while (i * i <= n) {
			ret += self(self, n / i);
			i++;
		}
		while (i <= n) {
			int j = n / (n / i);
			ret += self(self, n / i) * (j - i + 1);
			i = j + 1;
		}
		if (n <= 1'000'000) c1[n] = ret;
		else c2[n] = ret;
		return ret;
	};
	int n; cin >> n;
	cout << rec(rec, n) << '\n';
}