#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 998'244'353;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int mul(int a, int b) {
	return i64(a) * b % mod;
}

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

auto sol = [](int n, int m, auto e) {
	vector p(m + 1, 1);
	for (int i = 1; i <= m; i++) {
		p[i] = mul(p[i - 1], 2);
	}
	union_find uf(n + 1);
	int ret = 0;
	int cnt = 0;
	for (int i = m - 1; i >= 0; i--) {
		auto [a, b] = e[i];
		a = uf.find(a);
		b = uf.find(b);
		if (a == b) continue;
		if (cnt != n - 2) uf.merge(a, b), cnt++;
		else ret = add(ret, p[i + 1]);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector e(m, array{ 0, 0 });
	for (auto& [a, b] : e) cin >> a >> b;
	cout << sol(n, m, e) << '\n';
}