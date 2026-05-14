#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

template<int mod>
struct modint {
	constexpr modint() : r(0) {}
	constexpr modint(int x) : r(x % mod) { if (r < 0) r += mod; }
	constexpr modint(i64 x) : r(x % mod) { if (r < 0) r += mod; }
	static modint pow(modint x, i64 n) {
		modint ret = 1;
		for (; n; n >>= 1, x *= x) if (n & 1) ret *= x;
		return ret;
	}
	modint inv() const { return pow(*this, mod - 2); }
	modint operator- () const { return r ? mod - r : 0; }
	modint operator+ (const modint& x) const { return modint(*this) += x; }
	modint operator- (const modint& x) const { return modint(*this) -= x; }
	modint operator* (const modint& x) const { return modint(*this) *= x; }
	modint operator/ (const modint& x) const { return modint(*this) /= x; }
	modint& operator+= (const modint& x) { r = r - mod < -x.r ? r + x.r : r - mod + x.r; return *this; }
	modint& operator-= (const modint& x) { r = r < x.r ? r - x.r + mod : r - x.r; return *this; }
	modint& operator*= (const modint& x) { r = (i64)r * x.r % mod; return *this; }
	modint& operator/= (const modint& x) { return *this *= x.inv(); }
	bool operator== (const modint& x) const { return r == x.r; }
	bool operator!= (const modint& x) const { return r != x.r; }
	operator int() const { return r; }
	friend istream& operator>> (istream& in, modint& x) { i64 t; in >> t; x = modint(t); return in; }
	friend ostream& operator<< (ostream& out, const modint& x) { return out << x.r; }
private:
	int r;
};

using mint = modint<1'000'000'007>;

auto f = [](int n) {
	if (n <= 3) return mint(1);
	vector dp(n - 1, mint(0));
	dp[0] = 1;
	for (int iter = 4; iter <= n; iter++) {
		if (iter % 2 == 1) {
			for (int i = iter - 4; i >= 0; i--) dp[i] += dp[i + 1];
		}
		else {
			for (int i = 1; i <= iter - 3; i++) dp[i] += dp[i - 1];
			for (int i = iter - 3; i >= 0; i--) dp[i + 1] = dp[i];
			dp[0] = 0;
		}
	}
	mint ret = 0;
	for (int i = 0; i < n - 1; i++) ret += dp[i];
	return ret;
};

auto bino = [](int n, int k) {
	if (k == 0 || k == n) return mint(1);
	mint a = 1, b = 1;
	for (int i = 0; i < k; i++) {
		a *= mint(n - i);
		b *= mint(i + 1);
	}
	return a / b;
};

auto sol = [](int n, auto a, auto b) {
	vector pa(a.size() + 1, 0);
	vector pb(b.size() + 1, 0);
	for (int i = 0; i < a.size(); i++) pa[i + 1] = pa[i] + a[i];
	for (int i = 0; i < b.size(); i++) pb[i + 1] = pb[i] + b[i];
	vector buc(0, 0);
	for (int i = 1, j = 1, prv = 0; i <= a.size(); i++) {
		while (j <= b.size() && pa[i] > pb[j]) j++;
		if (j > b.size() || pa[i] != pb[j]) continue;
		if (a[i - 1] == 1 || b[j - 1] == 1) buc.push_back(pa[i] - prv);
		prv = pa[i];
	}
	int opt = 0, acc = 0;
	mint cnt = 1;
	for (int x : buc) {
		if (x == 1) continue;
		opt += x - 1;
		cnt *= f(x) * bino(acc + x - 1, x - 1);
		acc += x - 1;
	}
	return pair(opt, cnt);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	int sa; cin >> sa;
	vector a(sa, 0);
	for (int i = 0; i < sa; i++) cin >> a[i];
	int sb; cin >> sb;
	vector b(sb, 0);
	for (int i = 0; i < sb; i++) cin >> b[i];
	auto [opt, cnt] = sol(n, a, b);
	cout << opt << ' ' << cnt << '\n';
}