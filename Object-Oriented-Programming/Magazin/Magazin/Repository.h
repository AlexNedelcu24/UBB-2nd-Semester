#pragma once
#include "Produs.h"
#include <vector>
using std::vector;

class RepoException {
private:
	string errors;
public:
	RepoException(string errors) :errors{ errors } {};
	string getErrors() {
		return this->errors;
	}
};

class ProduseRepo {
private:
	vector<Produs> lista_produse;
public:
	ProduseRepo() = default;

	ProduseRepo(const ProduseRepo& o) = delete;

	void store(const Produs& p);

	void remove(const Produs& p);

	void modific(const Produs& p);

	const vector<Produs>& getProduse() noexcept ;

	const Produs& find(string nume);

	bool exista(const Produs& p);
};

void testeRepo();