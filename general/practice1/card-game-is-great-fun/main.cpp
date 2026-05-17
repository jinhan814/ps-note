#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector psum(n + 1, 0);
	for (int i = 0; i < n; i++) {
		psum[i + 1] = psum[i] + v[i][2];
	}
	vector c(2, vector((n + 1) * (n + 1) * (n + 1), false));
	deque q(0, tuple(0, 0, 0, 0));
	if (n >= 1) {
		c[0][(n + 1) * (n + 1)] = true;
		q.push_back(tuple(0, 1, 0, 0));
	}
	if (n >= 3) {
		c[1][1] = true;
		q.push_back(tuple(1, 0, 0, 1));
	}
	int ret = 0;
	while (q.size()) {
		auto [f, v1, v2, v3] = q.front(); q.pop_front();
		if (f == 0) {
			int val = psum[v1];
			if (v2 > 0) val += psum[v1 + v2 + 1] - psum[v1 + 1];
			ret = max(ret, val);
			int a = v[v3][0];
			int b = v[v3][1];
			if (v1 < n && (v[v1][0] == a || v[v1][1] == b)) {
				int nf = 0;
				int nv1 = v1 + v2 + 1;
				int nv2 = 0;
				int nv3 = v1;
				int p = nv1 * (n + 1) * (n + 1) + nv2 * (n + 1) + nv3;
				if (!c[nf][p]) {
					c[nf][p] = true;
					q.push_back(tuple(nf, nv1, nv2, nv3));
				}
			}
			if (v1 + v2 + 2 < n && (v[v1 + v2 + 2][0] == a || v[v1 + v2 + 2][1] == b)) {
				int nf = 1;
				int nv1 = v1;
				int nv2 = v2;
				int nv3 = 1;
				int p = nv1 * (n + 1) * (n + 1) + nv2 * (n + 1) + nv3;
				if (!c[nf][p]) {
					c[nf][p] = true;
					q.push_back(tuple(nf, nv1, nv2, nv3));
				}
			}
		}
		else {
			int val = psum[v1];
			if (v2 > 0) val += psum[v1 + v2 + 1] - psum[v1 + 1];
			if (v3 > 0) val += psum[v1 + v2 + v3 + 2] - psum[v1 + v2 + 2];
			ret = max(ret, val);
			int a = v[v1 + v2 + v3 + 1][0];
			int b = v[v1 + v2 + v3 + 1][1];
			if (v1 < n && (v[v1][0] == a || v[v1][1] == b)) {
				int nf = 0;
				int nv1 = v1 + v2 + 1;
				int nv2 = v3;
				int nv3 = v1;
				int p = nv1 * (n + 1) * (n + 1) + nv2 * (n + 1) + nv3;
				if (!c[nf][p]) {
					c[nf][p] = true;
					q.push_back(tuple(nf, nv1, nv2, nv3));
				}
			}
			if (v1 + v2 + v3 + 2 < n && (v[v1 + v2 + v3 + 2][0] == a || v[v1 + v2 + v3 + 2][1] == b)) {
				int nf = 1;
				int nv1 = v1;
				int nv2 = v2;
				int nv3 = v3 + 1;
				int p = nv1 * (n + 1) * (n + 1) + nv2 * (n + 1) + nv3;
				if (!c[nf][p]) {
					c[nf][p] = true;
					q.push_back(tuple(nf, nv1, nv2, nv3));
				}
			}
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i][0] >> v[i][1] >> v[i][2];
	cout << sol(n, v) << '\n';
}