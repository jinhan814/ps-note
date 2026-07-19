#include "cup.h"
#include <bits/stdc++.h>
using namespace std;

constexpr int lim = 1'000'000'000;

vector<int> find_cup() {
	int val = ask_shahrasb(-lim, -lim);
	int acc = 0;
	for (int bit = 0; bit <= 30; bit++) {
		int res = ask_shahrasb((1 << bit) - lim, -lim);
		if (val >> bit & 1) res += 1 << bit;
		else res -= 1 << bit;
		if (res == val) acc ^= 1 << bit;
	}
	return { acc - lim, (val ^ acc) - lim };
}