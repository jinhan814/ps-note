#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int a, int b) {
	vector adj(n, vector(n, vector(0, 0)));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int k = (a * j + b * i) % n;
			adj[j][k].push_back(i);
		}
	}
	vector c(n, vector(n, false));
	vector q(0, pair(0, 0));
	for (int i = 0; i < n; i++) {
		c[0][i] = true;
		q.push_back(pair(0, i));
		if (i > 0) {
			c[i][0] = true;
			q.push_back(pair(i, 0));
		}
	}
	while (q.size()) {
		auto [j, k] = q.back(); q.pop_back();
		for (int i : adj[j][k]) {
			if (c[i][j]) continue;
			c[i][j] = true;
			q.push_back(pair(i, j));
		}
	}
	int ret = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (c[i][j]) continue;
			ret++;
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, a, b; cin >> n >> a >> b;
	cout << sol(n, a, b) << '\n';
}