#include <bits/stdc++.h>
using namespace std;

auto sol = [](int a, int b, int c) {
	vector ret(1, 0);
	int p = 0;
	if (c % 3 == 0) {
		for (int i = 3; i <= c; i += 3) ret.push_back(i);
		for (int i = c + 1; i >= 1; i -= 3) ret.push_back(i);
		for (int i = 2; i <= c + 2; i += 3) ret.push_back(i);
		a -= 2;
		p += c + 2;
	}
	else if (c % 3 == 1) {
		for (int i = 3; i <= c + 2; i += 3) ret.push_back(i);
		for (int i = c; i >= 1; i -= 3) ret.push_back(i);
		for (int i = 2; i <= c + 1; i += 3) ret.push_back(i);
		ret.push_back(c + 3);
		a -= 1;
		b -= 2;
		p += c + 3;
	}
	else {
		for (int i = 3; i <= c + 1; i += 3) ret.push_back(i);
		for (int i = c; i >= 2; i -= 3) ret.push_back(i);
		for (int i = 1; i <= c + 2; i += 3) ret.push_back(i);
		a -= 2;
		p += c + 2;
	}
	for (int i = 1; i <= a - 1; i++) ret.push_back(p + i);
	p += a - 1;
	for (int i = 2; i <= b + 1; i += 2) ret.push_back(p + i);
	for (int i = b / 2 * 2 + 1; i >= 1; i -= 2) ret.push_back(p + i);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int a, b, c; cin >> a >> b >> c;
		auto res = sol(a, b, c);
		for (int x : res) cout << x << ' ';
		cout << '\n';
	}
}