#pragma once
#include "Produs.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using std::vector;
class Cos {
private:
	vector<Produs> lista;
public:
	Cos() = default;

	void add(const Produs& p);

	void empty();

	void addRandom(vector<Produs> produse, int nr);

	const vector<Produs>& getAll();

	bool Export(const string fname, const string type);
};

void testCos();