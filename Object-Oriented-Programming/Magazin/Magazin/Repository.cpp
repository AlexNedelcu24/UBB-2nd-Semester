#include "Repository.h"
#include <assert.h>
//#include "gsl.h"

bool ProduseRepo::exista(const Produs& p) {
	try {
		find(p.getNume());
	}
	catch (RepoException) {
		return false;
	}
}

const Produs& ProduseRepo::find(string nume) {

	vector<Produs>::iterator f = std::find_if(this->lista_produse.begin(), this->lista_produse.end(),
		[=](const Produs& p) {
			return p.getNume() == nume;
		});

	if (f != this->lista_produse.end())
		return (*f);
	else
		throw RepoException("Produsul cu numele " + nume + " nu exista.");

}

void ProduseRepo::store(const Produs& p) {
	if (exista(p)) {
		throw RepoException("Produsul cu numele " + p.getNume() + " si tipul " + p.getTip() + " exista deja.");
	}
	this->lista_produse.push_back(p);
}

void ProduseRepo::remove(const Produs& p) {
	/*if (!exista(p)) {
		throw RepoException("Produsul cu numele " + p.getNume() + " si tipul " + p.getTip() + " nu exista.");
	}
	IteratorVector<Produs> ic = this->lista_produse.begin();
	int i = 0;
	while (ic.valid())
	{
		if (ic.element().getNume() == p.getNume() && ic.element().getTip() == p.getTip() && ic.element().getPret() == p.getPret() && ic.element().getProducator() == p.getProducator()) {
			this->lista_produse.sterge(i);
			break;
		}
		i++;
		ic.next();
	}
	*/
	if (!exista(p)) {
		throw RepoException("Produsul cu numele " + p.getNume() + " nu exista.");
	}
	vector<Produs>::iterator f = std::find_if(this->lista_produse.begin(), this->lista_produse.end(),
		[=](const Produs& p2) {
			return p2.getNume() == p.getNume() && p2.getTip() == p.getTip() && p2.getProducator() == p.getProducator() && p2.getPret() == p.getPret();
		});

	if (f != this->lista_produse.end())
		this->lista_produse.erase(f);
}

void ProduseRepo::modific(const Produs& p) {
	if (!exista(p)) {
		throw RepoException("Produsul cu numele " + p.getNume() + " si tipul " + p.getTip() + " nu exista.");
	}
	/*IteratorVector<Produs> ic = this->lista_produse.begin();
	int i = 0;
	while (ic.valid())
	{
		if (ic.element().getNume() == p.getNume() && ic.element().getTip() == p.getTip() && ic.element().getPret() == p.getPret() && ic.element().getProducator() == p.getProducator()) {
			this->lista_produse.set(p_nou, i);
			break;
		}
		i++;
	}*/

	/*vector<Produs>::iterator f = std::find_if(this->lista_produse.begin(), this->lista_produse.end(),
		[=](const Produs& p2) {
			return p2.getNume() == p.getNume() && p2.getTip() == p.getTip() && p2.getProducator() == p.getProducator() && p2.getPret() == p.getPret();
		});


	int poz = distance(this->lista_produse.begin(), f);

	this->lista_produse[poz].setNume(p_nou.getNume());
	this->lista_produse[poz].setTip(p_nou.getTip());
	this->lista_produse[poz].setProducator(p_nou.getProducator());
	this->lista_produse[poz].setPret(p_nou.getPret());
	*/
	else
	{
		for (auto& produs : lista_produse)
		{
			if (p.getNume() == produs.getNume())
			{
			    produs = p;
				break;
			}
		}
	}

}

const vector<Produs>& ProduseRepo::getProduse() noexcept {
	return this->lista_produse;
}

void teststore() {
	ProduseRepo testr;
	Produs a{ "nume1", "tip1","prod1", 1.99 };
	testr.store(a);
	assert(testr.getProduse().size() == 1);

	Produs b{ "nume2", "tip2", "prod2", 5.99 };

	testr.store(b);
	assert(testr.getProduse().size() == 2);

	assert(testr.getProduse().at(1).getNume() == "nume2");

	/*Produs c{"nume2", "", "prod2", 5.99};
	try {
		testr.store(c);
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}*/

}

void testremove() {
	ProduseRepo testr;
	Produs a{ "nume1", "tip1","prod1", 1.99 };
	Produs b{ "nume2", "tip2", "prod2", 5.99 };
	Produs c{ "nume3", "tip3", "prod3", 4.11 };

	testr.store(a);
	testr.store(b);

	assert(testr.getProduse().size() == 2);

	testr.remove(a);

	assert(testr.getProduse().size() == 1);

	assert(testr.getProduse().at(0).getPret() == 5.99);

	try {
		testr.remove(c);
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}
}

void testmodific() {
	ProduseRepo testr;
	Produs a{ "nume1", "tip1","prod1", 5.99 };
	Produs b{ "nume1", "tip1", "prod2", 5.99 };
	Produs c{ "nume3", "tip1", "prod3", 5.99 };
	Produs d{ "nume4", "tip4", "prod4", 1.22 };

	testr.store(a);

	testr.modific(b);
    testr.store(c);
	assert(testr.getProduse().at(1).getPret() == testr.getProduse().at(0).getPret());
	assert(testr.getProduse().at(1).getTip() == testr.getProduse().at(0).getTip());

	try {
		testr.modific(d);
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}
}

void testFind() {
	ProduseRepo testr;

	Produs a{ "nume1", "tip1","prod1", 1.99 };
	Produs b{ "nume2", "tip2", "prod2", 5.99 };
	Produs c{ "nume3","tip3", "prod3", 9.99 };
	testr.store(a);
	testr.store(b);

	assert(testr.exista(a));
	assert(!testr.exista(c));

	auto foundProdus = testr.find("nume1");
	assert(foundProdus.getTip() == "tip1");
	assert(foundProdus.getPret() == 1.99);
	assert(foundProdus.getProducator() == "prod1");

	try {
		testr.find("nume5");
		assert(false);
	}
	catch (RepoException& ve) {
		assert(ve.getErrors() == "Produsul cu numele nume5 nu exista.");
	}

}

void testeRepo() {
	teststore();
	testremove();
	testmodific();
    testFind();
}