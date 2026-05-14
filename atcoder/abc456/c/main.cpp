#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 119 << 23 | 1;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

auto sol = [](string s) {
	int ret = 0;
	for (int i = 0, j = 0; i < s.size(); i++) {
		if (j < i) j = i;
		while (j + 1 < s.size() && s[j] != s[j + 1]) j++;
		ret = add(ret, j - i + 1);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	cout << sol(s) << '\n';
}