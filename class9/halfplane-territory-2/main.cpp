#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct hull {
	void push(int a, int b) {
		while (data.size() > 1) {
			auto [a1, b1] = data.end()[-2];
			auto [a2, b2] = data.back();
			i64 r1 = 1LL * (b1 - b2) * (a - a2);
			i64 r2 = 1LL * (b2 - b) * (a2 - a1);
			if (r1 < r2) break;
			data.pop_back();
		}
		data.push_back({ a, b });
	}
	i64 query(int x) {
		if (data.empty()) return -(1LL << 60);
		while (data.size() > 1) {
			auto [a1, b1] = data.end()[-2];
			auto [a2, b2] = data.back();
			i64 r1 = 1LL * a1 * x + b1;
			i64 r2 = 1LL * a2 * x + b2;
			if (r1 < r2) break;
			data.pop_back();
		}
		auto [a, b] = data.back();
		return 1LL * a * x + b;
	}
private:
	vector<array<int, 2>> data;
};

auto sol = [](int q, auto qs) {
	vector a(0, array{ 0, 0 });
	vector b(0, array{ 0, 0 });
	vector c(q, 0);
	for (int i = 0; i < q; i++) {
		if (qs[i][0] != 2) continue;
		a.push_back({ qs[i][1] - 1, i - 1 });
		c[qs[i][1] - 1] = 1;
	}
	for (int i = 0; i < q; i++) {
		if (qs[i][0] != 1 || c[i]) continue;
		a.push_back({ i, q - 1 });
	}
	for (int i = 0, p = 0; i < q; i++) {
		if (qs[i][0] != 3) continue;
		b.push_back({ i, p++ });
	}
	sort(a.begin(), a.end(), [&](auto a, auto b) {
		return qs[a[0]][1] < qs[b[0]][1];
	});
	sort(b.begin(), b.end(), [&](auto a, auto b) {
		return qs[a[0]][1] > qs[b[0]][1];
	});
	int sz = 1 << __lg(q - 1) + 1;
	vector tree(sz << 1, hull{});
	auto push = [&](int l, int r, int a, int b) {
		for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) tree[l++].push(a, b);
			if (~r & 1) tree[r--].push(a, b);
		}
	};
	auto query = [&](int i, int x) {
		i64 ret = -(1LL << 60);
		for (i |= sz; i; i >>= 1) ret = max(ret, tree[i].query(x));
		return ret;
	};
	vector res(b.size(), 0LL);
	for (auto [l, r] : a) push(l, r, qs[l][1], qs[l][2]);
	for (auto [i, p] : b) res[p] = query(i, qs[i][1]);
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int q; cin >> q;
	vector qs(q, array{ 0, 0, 0 });
	for (auto& [t, a, b] : qs) {
		cin >> t >> a;
		if (t == 1) cin >> b;
	}
	auto res = sol(q, qs);
	for (i64 x : res) {
		if (x == -(1LL << 60)) cout << "EMPTY SET" << '\n';
		else cout << x << '\n';
	}
}