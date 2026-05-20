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

auto sol = [](int n, int q, auto v, auto qs) {
	vector uf(19, union_find(n));
	int acc = 0;
	auto rec = [&](const auto& self, int bit, int a, int b) -> void {
		if (uf[bit].find(a) == uf[bit].find(b)) return;
		if (bit == 0) {
			a = uf[bit].find(a);
			b = uf[bit].find(b);
			int val = add(v[a], v[b]);
			acc = add(acc, mul(v[a], v[b]));
			uf[bit].merge(a, b);
			v[uf[bit].find(a)] = val;
		}
		else {
			uf[bit].merge(a, b);
			int sz = 1 << (bit - 1);
			self(self, bit - 1, a, b);
			self(self, bit - 1, a + sz, b + sz);
		}
	};
	vector ret(q, 0);
	for (int i = 0; i < q; i++) {
		auto [k, a, b] = qs[i];
		for (int bit = 18; bit >= 0; bit--) {
			if (~k >> bit & 1) continue;
			rec(rec, bit, a, b);
			a += 1 << bit;
			b += 1 << bit;
		}
		ret[i] = acc;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n, 0);
	vector qs(q, array{ 0, 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i];
	for (auto& [k, a, b] : qs) cin >> k >> a >> b;
	auto res = sol(n, q, v, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}