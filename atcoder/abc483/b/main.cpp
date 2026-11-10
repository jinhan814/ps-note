#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int q, auto qs) {
	vector ret(n, 0);
	for (int i = 0; i < n; i++) ret[i] = i + 1;
	for (int x : qs) {
		for (int i = 0; i < x; i++) {
			if (i < x - i - 1) swap(ret[i], ret[x - i - 1]);
			ret[i] = -ret[i];
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector qs(q, 0);
	for (int i = 0; i < q; i++) cin >> qs[i];
	auto res = sol(n, q, qs);
	for (int i = 0; i < n; i++) cout << res[i] << '\n';
}