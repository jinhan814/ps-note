#include <bits/stdc++.h>
using namespace std;

auto sol = [](int a, int b, int c) {
	vector ret(1, 0);
	int d = 0;
	if (c % 3 == 0) {
		for (int i = 3; i <= c; i += 3) ret.push_back(i);
		for (int i = c + 1; i >= 1; i -= 3) ret.push_back(i);
		for (int i = 2; i <= c + 2; i += 3) ret.push_back(i);
		a -= 2;
		d += c + 2;
	}
	else if (c % 3 == 1) {
		for (int i = 3; i <= c + 2; i += 3) ret.push_back(i);
		for (int i = c; i >= 1; i -= 3) ret.push_back(i);
		for (int i = 2; i <= c + 1; i += 3) ret.push_back(i);
		ret.push_back(c + 3);
		a -= 1;
		b -= 2;
		d += c + 3;
	}
	else {
		for (int i = 3; i <= c + 1; i += 3) ret.push_back(i);
		for (int i = c; i >= 2; i -= 3) ret.push_back(i);
		for (int i = 1; i <= c + 2; i += 3) ret.push_back(i);
		a -= 2;
		d += c + 2;
	}
	while (a > 1) {
		ret.push_back(d + 1);
		a -= 1;
		d += 1;
	}
	if (b % 2 == 0) {
		for (int i = 2; i <= b; i += 2) ret.push_back(d + i);
		for (int i = b + 1; i >= 1; i -= 2) ret.push_back(d + i);
	}
	else {
		for (int i = 2; i <= b + 1; i += 2) ret.push_back(d + i);
		for (int i = b; i >= 1; i -= 2) ret.push_back(d + i);
	}
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