#include <bits/stdc++.h>
using namespace std;

struct union_find {
	union_find(int n) : p(n, -1) {}
	int find(int x) {
		return p[x] < 0 ? x : p[x] = find(p[x]);
	}
	void merge(int a, int b) {
		a = find(a);
		b = find(b);
		if (a != b) p[b] = a;
	}
private:
	vector<int> p;
};

auto sol = [](int n, int m, int k, auto v) {
	vector buc1(n + 1, vector(0, 0));
	vector buc2(m + 1, vector(0, 0));
	for (int i = 0; i < k; i++) {
		buc1[v[i][0]].push_back(v[i][1]);
		buc2[v[i][1]].push_back(v[i][0]);
	}
	union_find uf1(n + 1);
	union_find uf2(m + 1);
	for (int i = 1; i <= n; i++) {
		if (buc1[i].empty()) continue;
		for (int j : buc1[i]) uf2.merge(buc1[i][0], j);
	}
	for (int i = 1; i <= m; i++) {
		if (buc2[i].empty()) continue;
		for (int j : buc2[i]) uf1.merge(buc2[i][0], j);
	}
	int ret = -1;
	for (int i = 1; i <= n; i++) {
		if (i != uf1.find(i)) continue;
		if (buc1[i].size()) continue;
		ret++;
	}
	for (int i = 1; i <= m; i++) {
		if (i != uf2.find(i)) continue;
		ret++;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(k, array{ 0, 0 });
	for (int i = 0; i < k; i++) cin >> v[i][0] >> v[i][1];
	cout << sol(n, m, k, v) << '\n';
}