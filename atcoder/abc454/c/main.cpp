#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector adj(n + 1, vector(0, 0));
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
	}
	vector c(n + 1, false); c[1] = 1;
	vector q(1, 1);
	while (q.size()) {
		int x = q.back(); q.pop_back();
		for (int i : adj[x]) {
			if (c[i]) continue;
			c[i] = true;
			q.push_back(i);
		}
	}
	int res = 0;
	for (int i = 1; i <= n; i++) {
		if (!c[i]) continue;
		res++;
	}
	cout << res << '\n';
}