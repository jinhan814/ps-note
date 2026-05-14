#include <bits/stdc++.h>
using namespace std;

struct union_find {
	union_find(int n) : p(n, -1) {}
	int find(int x) {
		return p[x] < 0 ? x : p[x] = find(p[x]);
	}
	bool merge(int a, int b) {
		a = find(a);
		b = find(b);
		if (a == b) return 0;
		p[b] = a;
		return 1;
	}
private:
	vector<int> p;
};

auto sol = [](int n, int m, int k, auto adj) {
	vector e(0, array{ 0, 0, 0 });
	for (int i = 1; i <= n; i++) {
		for (int j : adj[i]) {
			if (i > j) continue;
			int cost = adj[i].size() + adj[j].size();
			e.push_back(array{ cost, i, j });
		}
	}
	sort(e.begin(), e.end());
	union_find uf(n + 1);
	int ret = 0;
	for (auto [cost, a, b] : e) {
		if (!uf.merge(a, b)) continue;
		ret += cost;
	}
	for (int i = 1; i <= n; i++) {
		if (i == k) continue;
		ret -= adj[i].size();
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector adj(n + 1, vector(0, 0));
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	cout << sol(n, m, k, adj) << '\n';
}