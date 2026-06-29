#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, int q, auto qs) {
	vector ret(n, string(m, ' '));
	for (int iter = q - 1; iter >= 0; iter--) {
		auto [a, b, c] = qs[iter];
		for (int i = a - 1; i >= 0; i--) {
			if (ret[i][b - 1] != ' ') break;
			for (int j = b - 1; j >= 0; j--) {
				if (ret[i][j] != ' ') break;
				ret[i][j] = c;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (ret[i][j] != ' ') continue;
			ret[i][j] = 'A';
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, q; cin >> n >> m >> q;
	vector qs(q, tuple(0, 0, ' '));
	for (auto& [a, b, c] : qs) cin >> a >> b >> c;
	auto res = sol(n, m, q, qs);
	for (int i = 0; i < n; i++) cout << res[i] << '\n';
}