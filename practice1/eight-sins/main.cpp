#include <bits/stdc++.h>
using namespace std;

using f64 = double;

auto log_bino = [](int n, int k) {
	if (k < 0 || k > n) return f64(-1e99);
	if (k == 0 || k == n) return f64(0);
	if (k > n - k) k = n - k;
	f64 ret = 0;
	for (int i = 0; i < k; i++) {
		ret += log(n - i);
		ret -= log(i + 1);
	}
	return ret;
};

auto log_sum = [](f64 a, f64 b) {
	if (a > b) swap(a, b);
	return log(exp(a - b) + 1) + b;
};

auto calc = [](int n, int k, int lo, int hi) {
	int l = lo, r = hi + 1;
	while (l + 1 < r) {
		int mid = (l + r) / 2;
		f64 v1 = log_bino(k - lo + 1, n);
		f64 v2 = log_bino(k - mid + 1, n);
		f64 v3 = log_bino(k - hi, n);
		if (log_sum(v1, v3) <= log_sum(v2, v2)) l = mid;
		else r = mid;
	}
	return l;
};

int main() {
	int n, k; cin >> n >> k;
	for (int prv = 0; n > 0; n--) {
		int lo = prv + 1, hi = k - n + 1;
		bool flag = false;
		while (lo != hi) {
			int mid = calc(n, k, lo, hi);
			cout << mid << endl;
			char c; cin >> c;
			if (c == '=') { prv = mid; flag = true; break; }
			if (c == '<') hi = mid - 1;
			else lo = mid + 1;
		}
		if (!flag) {
			cout << lo << endl;
			char c; cin >> c;
			prv = lo;
		}
	}
}