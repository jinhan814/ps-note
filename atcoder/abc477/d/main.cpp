#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int q, auto qs) {
	vector buc(n, vector(1, -1));
	vector pos(q, -1);
	for (int i = 0; i < q; i++) {
		auto [op, x] = qs[i];
		if (op == 1) buc[x].push_back(i);
		else pos[i] = i;
	}
	for (int i = 0; i < n; i++) {
		buc[i].push_back(q);
	}
	for (int i = 1; i < q; i++) {
		pos[i] = max(pos[i], pos[i - 1]);
	}
	string ret(n, 'a');
	for (int i = 0; i < n; i++) {
		for (int j = buc[i].size() - 2; j >= 0; j--) {
			if (j % 2 == 1) continue;
			int l = buc[i][j] + 1;
			int r = buc[i][j + 1] - 1;
			if (r < 0 || pos[r] < l) continue;
			ret[i] = qs[pos[r]][1];
			break;
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector qs(q, array{ 0, 0 });
	for (auto& [op, x] : qs) {
		char c;
		cin >> op;
		if (op == 1) cin >> x, x--;
		else cin >> c, x = c;
	}
	cout << sol(n, q, qs) << '\n';
}