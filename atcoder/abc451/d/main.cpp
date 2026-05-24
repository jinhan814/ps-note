#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	vector p(10, 1);
	for (int i = 1; i < 10; i++) p[i] = p[i - 1] * 10;
	vector c(30, 0);
	for (int i = 0; i < 30; i++) c[i] = p[to_string(1 << i).size()];
	vector cand(0, 0);
	auto rec = [&](const auto& self, int x) -> void {
		cand.push_back(x);
		for (int bit = 0; bit < 30; bit++) {
			i64 nx = i64(x) * c[bit] + (1 << bit);
			if (nx > 1'000'000'000) break;
			self(self, nx);
		}
	};
	rec(rec, 0);
	sort(cand.begin(), cand.end());
	cand.erase(unique(cand.begin(), cand.end()), cand.end());
	int n; cin >> n;
	cout << cand[n] << '\n';
}