#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct union_find {
	union_find(int n) : p(n, -1) {}
	int find(int x) {
		return p[x] < 0 ? x : p[x] = find(p[x]);
	}
	bool merge(int a, int b) {
		a = find(a);
		b = find(b);
		if (a == b) return false;
		p[b] = a;
		return true;
	}
private:
	vector<int> p;
};

auto sol = [](int n, auto v) {
	vector c(v[n - 1] + 1, -1);
	for (int i = 0; i < n; i++) c[v[i]] = i;
	i64 ret = 0;
	union_find uf(n);
	for (int x = v[n - 1]; x >= 1; x--) {
		for (int i = x, p = -1; i <= v[n - 1]; i += x) {
			if (c[i] == -1) continue;
			if (p != -1 && uf.merge(p, c[i])) ret += x;
			p = c[i];
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}