#include <bits/stdc++.h>
using namespace std;

auto sol = [](auto v) {
	int ret = 1 << 30;
	for (int i = 0; i < 5; i++) {
		int v1 = 0, v2 = 0;
		for (int j = 0; j < 5; j++) {
			if (v[i][j] == '.') v1++;
			if (v[j][i] == '.') v2++;
		}
		ret = min(ret, min(v1, v2));
	}
	{
		int v1 = 0, v2 = 0;
		for (int i = 0; i < 5; i++) {
			if (v[i][i] == '.') v1++;
			if (v[i][4 - i] == '.') v2++;
		}
		ret = min(ret, min(v1, v2));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	vector v(5, string{});
	for (int i = 0; i < 5; i++) cin >> v[i];
	cout << sol(v) << '\n';
}