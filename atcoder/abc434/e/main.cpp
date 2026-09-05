#include <bits/stdc++.h>
using namespace std;

struct union_find {
	union_find(int n) : p(n, -1) {}
	int find(int x) {
		return p[x] < 0 ? x : p[x] = find(p[x]);
	}
	int cnt(int x) {
		return -p[find(x)];
	}
	bool merge(int a, int b) {
		a = find(a);
		b = find(b);
		if (a == b) return false;
		p[a] += p[b];
		p[b] = a;
		return true;
	}
private:
	vector<int> p;
};

auto sol = [](int n, auto v) {
	vector c(0, 0);
	for (auto [a, b] : v) {
		c.push_back(a - b);
		c.push_back(a + b);
	}
	sort(c.begin(), c.end());
	c.erase(unique(c.begin(), c.end()), c.end());
	union_find uf(c.size());
	for (auto [a, b] : v) {
		int p1 = lower_bound(c.begin(), c.end(), a - b) - c.begin();
		int p2 = lower_bound(c.begin(), c.end(), a + b) - c.begin();
		uf.merge(p1, p2);
	}
	vector cnt(c.size(), 0);
	for (auto [a, b] : v) {
		int p = lower_bound(c.begin(), c.end(), a - b) - c.begin();
		cnt[uf.find(p)]++;
	}
	int ret = 0;
	for (int i = 0; i < c.size(); i++) {
		if (uf.find(i) != i) continue;
		ret += uf.cnt(i);
		if (cnt[i] == uf.cnt(i) - 1) ret--;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0 });
	for (auto& [a, b] : v) cin >> a >> b;
	cout << sol(n, v) << '\n';
}