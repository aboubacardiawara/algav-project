#include <iostream>
#include <cassert>
#include "../main/warming_up.h"

using namespace std;

void testDecomposition()
{
	vector<bool> v = decomposition(38);
	vector<bool> expected = {false, true, true, false, false, true};
	assert(v == expected && "testDecomposition");
}

void testCompletion()
{
	// tronc
	vector<bool> v1 = {false, true, true, false, false, true};
	vector<bool> expected1 = {false, true, true, false, false, true};
	assert(completion(v1, 4) == expected1);

	// expand
	vector<bool> v2 = {false, true, true, false, false, true};
	vector<bool> expected2 = {false, true, true, false, false, true, false, false};
	assert(completion(v2, 8) == expected2);
}

int main() {
	testDecomposition();
	testCompletion();
	return 0;
}