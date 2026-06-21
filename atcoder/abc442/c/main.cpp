#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, auto adj) {
	vector ret(n + 1, i64(0));
	for (int i = 1; i <= n; i++) {
		i64 val = n - adj[i].size() - 1;
		ret[i] = val * (val - 1) * (val - 2) / 6;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector adj(n + 1, vector(0, 0));
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	auto res = sol(n, m, adj);
	for (int i = 1; i <= n; i++) cout << res[i] << ' ';
	cout << '\n';
}