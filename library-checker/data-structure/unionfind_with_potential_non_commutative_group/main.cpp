#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 998'244'353;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int sub(int a, int b) {
	return a < b ? a - b + mod : a - b;
}

constexpr int mul(int a, int b) {
	return i64(a) * b % mod;
}

auto matinv = [](auto v) {
	swap(v[0], v[3]);
	v[1] = sub(0, v[1]);
	v[2] = sub(0, v[2]);
	return v;
};

auto matmul = [](auto a, auto b) {
	vector ret(4, 0);
	ret[0] = add(mul(a[0], b[0]), mul(a[1], b[2]));
	ret[1] = add(mul(a[0], b[1]), mul(a[1], b[3]));
	ret[2] = add(mul(a[2], b[0]), mul(a[3], b[2]));
	ret[3] = add(mul(a[2], b[1]), mul(a[3], b[3]));
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector p(n + 1, -1);
	vector v(n + 1, vector{ 1, 0, 0, 1 });
	auto find = [&](const auto& self, int i) -> int {
		if (p[i] == -1) return i;
		if (p[p[i]] == -1) return p[i];
		self(self, p[i]);
		v[i] = matmul(v[i], v[p[i]]);
		p[i] = p[p[i]];
		return p[i];
	};
	while (q--) {
		int op; cin >> op;
		if (op == 0) {
			int a, b; cin >> a >> b;
			vector x(4, 0);
			for (int i = 0; i < 4; i++) cin >> x[i];
			int pa = find(find, a);
			int pb = find(find, b);
			if (pa == pb) {
				auto res = matmul(v[b], matinv(v[a]));
				cout << (x == res) << '\n';
			}
			else {
				v[pb] = matmul(matinv(v[b]), matmul(x, v[a]));
				p[pb] = pa;
				cout << 1 << '\n';
			}
		}
		else {
			int a, b; cin >> a >> b;
			int pa = find(find, a);
			int pb = find(find, b);
			if (pa == pb) {
				auto res = matmul(v[b], matinv(v[a]));
				for (int i = 0; i < 4; i++) cout << res[i] << ' ';
				cout << '\n';
			}
			else {
				cout << -1 << '\n';
			}
		}
	}
}