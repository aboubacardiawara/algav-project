#include <iostream>
#include <cassert>
#include "../main/warming_up.h"

using namespace std;

int main() {
	vector<bool> v = decomposition(38);
	vector<bool> expected = {false, true, true, false, false, true};
	assert(v == expected && "testDecomposition");
	return 0;
}