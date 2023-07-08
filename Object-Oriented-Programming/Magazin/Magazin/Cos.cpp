#include "Cos.h"
#include <assert.h>
#include <fstream>
using std::shuffle;
using std::ofstream;

#include <cassert>

void Cos::add(const Produs& p) {
	this->lista.push_back(p);
}

void Cos::empty() {
	this->lista.clear();
}

void Cos::addRandom(vector<Produs> produse, int nr) {
	shuffle(produse.begin(), produse.end(), std::default_random_engine(std::random_device{}())); //amesteca produsele
	while (lista.size() < nr && produse.size() > 0) {
		lista.push_back(produse.back());
		produse.pop_back();
	}
}

const vector<Produs>& Cos::getAll() {
	return this->lista;
}

bool Cos::Export(const string fname, const string type)
{
	string name = fname + '.' + type;
	ofstream out(name);
	if (type == "csv" || type == "html")
	{
		for (const Produs& produs : this->lista)
		{
			out << '\n';
			out << "Nume produs: " << produs.getNume() << '\n';
			out << "Producatorul produsului: " << produs.getProducator() << '\n';
			out << "Tipul produsului: " << produs.getTip() << '\n';
			out << "Pretul produsului: " << produs.getPret() << '\n';
			out << endl;
		}
		return true;
	}
	return false;
}

void testadd() {
	Cos testr;
	Produs a{ "nume1", "tip1","prod1", 1.99 };
	testr.add(a);
	assert(testr.getAll().size() == 1);

	Produs b{ "nume2", "tip2", "prod2", 5.99 };

	testr.add(b);
	assert(testr.getAll().size() == 2);

	assert(testr.getAll().at(1).getNume() == "nume2");

}

void testaddrandom() {
	Cos test;
	vector<Produs> produse;
	Produs a{ "nume1", "tip1","prod1", 1.99 };
	produse.push_back(a);
	Produs b{ "nume2", "tip2", "prod2", 5.99 };
	produse.push_back(b);


	test.addRandom(produse, 2);

	assert(test.getAll().size() == 2);

	test.empty();
	assert(test.getAll().size() == 0);
}

void testCos() {
	testadd();
	testaddrandom();
}