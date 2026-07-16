#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto adj) {
	vector ret(0, 0);
	auto rec = [&](const auto& self, auto buc) -> void {
		vector cand(0, pair(0, 0));
		for (int x : buc) {
			if (x) ret.push_back(x);
			for (auto [a, b] : adj[x]) cand.push_back(pair(a, b));
		}
		sort(cand.begin(), cand.end());
		for (int i = 0, j = 0; i < cand.size(); i = j) {
			while (j < cand.size() && cand[i].first == cand[j].first) j++;
			vector nbuc(0, 0);
			for (int k = i; k < j; k++) nbuc.push_back(cand[k].second);
			self(self, nbuc);
		}
	};
	rec(rec, vector(1, 0));
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector adj(n + 1, vector(0, pair(0, 0)));
	for (int i = 1; i <= n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(pair(b, i));
	}
	auto res = sol(n, adj);
	for (int x : res) cout << x << ' ';
	cout << '\n';
}