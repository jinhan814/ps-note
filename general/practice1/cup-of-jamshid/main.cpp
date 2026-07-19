#include "cup.h"
#include <bits/stdc++.h>
using namespace std;

constexpr int pos = -500'000'001;

vector<int> find_cup() {
	auto ask = [](int x, int y) { return ask_shahrasb(x + pos, y + pos); };
	int val = ask(0, 0);
	int acc = 0;
	for (int bit = 0; bit < 30; bit++) {
		int res = ask(1 << bit, 0);
		if (res == (val ^ (1 << bit))) acc ^= 1 << bit;
	}
	return { pos + acc, pos + (val ^ acc) };
}