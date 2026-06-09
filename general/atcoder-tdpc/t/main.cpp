#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 1'000'000'007;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int sub(int a, int b) {
	return a < b ? a - b + mod : a - b;
}

constexpr int mul(int a, int b) {
	return i64(a) * b % mod;
}

auto conv = [](auto a, auto b) {
	vector ret(a.size() + b.size() - 1, 0);
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < b.size(); j++) {
			int val = mul(a[i], b[j]);
			ret[i + j] = add(ret[i + j], val);
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int k; cin >> k;
	int n; cin >> n;
	vector a(k, 1);
	vector q(k + 1, sub(0, 1));
	q[0] = 1;
	auto p = conv(a, q);
	p.resize(k);
	for (n--; n; n >>= 1) {
		auto c = q;
		for (int i = 1; i <= k; i += 2) c[i] = sub(0, q[i]);
		auto np = conv(p, c);
		auto nq = conv(q, c);
		for (int i = 0; i < k; i++) p[i] = np[i << 1 | (n & 1)];
		for (int i = 0; i <= k; i++) q[i] = nq[i << 1];
	}
	cout << p[0] << '\n';
}