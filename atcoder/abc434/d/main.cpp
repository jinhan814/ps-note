#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector p1(2'002, vector(2'002, 0));
	for (auto [a, b, c, d] : v) {
		p1[a][c]++;
		p1[a][d + 1]--;
		p1[b + 1][c]--;
		p1[b + 1][d + 1]++;
	}
	for (int i = 1; i <= 2'000; i++) {
		for (int j = 0; j <= 2'000; j++) {
			p1[i][j] += p1[i - 1][j];
		}
	}
	for (int j = 1; j <= 2'000; j++) {
		for (int i = 0; i <= 2'000; i++) {
			p1[i][j] += p1[i][j - 1];
		}
	}
	int acc = 0;
	vector p2(2'001, vector(2'001, 0));
	for (int i = 1; i <= 2'000; i++) {
		for (int j = 1; j <= 2'000; j++) {
			if (p1[i][j] == 0) acc++;
			if (p1[i][j] == 1) p2[i][j] = 1;
		}
	}
	for (int i = 1; i <= 2'000; i++) {
		for (int j = 0; j <= 2'000; j++) {
			p2[i][j] += p2[i - 1][j];
		}
	}
	for (int j = 1; j <= 2'000; j++) {
		for (int i = 0; i <= 2'000; i++) {
			p2[i][j] += p2[i][j - 1];
		}
	}
	vector ret(n, acc);
	for (int i = 0; i < n; i++) {
		auto [a, b, c, d] = v[i];
		ret[i] += p2[a - 1][c - 1];
		ret[i] -= p2[a - 1][d];
		ret[i] -= p2[b][c - 1];
		ret[i] += p2[b][d];
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0, 0, 0 });
	for (auto& [a, b, c, d] : v) cin >> a >> b >> c >> d;
	auto res = sol(n, v);
	for (int i = 0; i < n; i++) cout << res[i] << '\n';
}