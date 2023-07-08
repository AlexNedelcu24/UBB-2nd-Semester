#include "Iterator.h"
#include "DO.h"
#include <algorithm>

using namespace std;

// Complexitate timp: ?(1)
void Iterator::deplasareTD() {
	while ((curent < dict.m) && dict.e[curent].first == NULL_TVALOARE)
		curent++;
}

// Complexitate timp: ?(1)
void Iterator::deplasare() {
	while ((curent < ord.size()) && ord[curent].first == NULL_TVALOARE)
		curent++;
}

// Complexitate timp: ?(n)
Iterator::Iterator(const DO& d) : dict(d) {
	curent = 0;
	deplasareTD();

	while (curent < dict.m) {
		ord.push_back({ dict.e[curent].first, dict.e[curent].second });
		curent++;
		deplasareTD();
	}

	sort(ord.begin(), ord.end(), dict.r);
	curent = 0;
	deplasare();
}

// Complexitate timp: ?(1)
void Iterator::prim() {
	curent = 0;
	deplasare();
}

// Complexitate timp: ?(1)
void Iterator::urmator() {
	curent++;
	deplasare();
}

// Complexitate timp: ?(1)
bool Iterator::valid() const {
	return curent < ord.size();
}

// Complexitate timp: ?(1)
TElem Iterator::element() const {
	return { ord[curent].first, ord[curent].second };
}
