#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto a, auto b, auto adj) {
	vector cand(n, 0);
	iota(cand.begin(), cand.end(), 1);
	sort(cand.begin(), cand.end(), [&](int i, int j) {
		return b[i] < b[j];
	});
	vector rev(n + 1, vector(0, 0));
	vector cnt(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		for (int j : adj[i]) {
			rev[j].push_back(i);
			cnt[i]++;
		}
	}
	vector c(n + 1, false);
	vector q(0, 0);
	auto push = [&](int x) {
		c[x] = true;
		for (int i : rev[x]) {
			if (c[i]) continue;
			if (--cnt[i] == 0) q.push_back(i);
		}
	};
	for (int iter = 1, pos = 0; iter <= n; iter++) {
		if (q.empty()) {
			while (c[cand[pos]]) pos++;
			push(cand[pos]);
		}
		else {
			int x = q.back(); q.pop_back();
			i64 acc = a[x];
			for (int i : adj[x]) acc += b[i];
			if (b[x] > acc) b[x] = acc;
			push(x);
		}
	}
	return b[1];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector a(n + 1, 0), b(n + 1, 0);
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i];
		int k; cin >> k;
		while (k--) {
			int x; cin >> x;
			adj[i].push_back(x);
		}
	}
	cout << sol(n, a, b, adj) << '\n';
}