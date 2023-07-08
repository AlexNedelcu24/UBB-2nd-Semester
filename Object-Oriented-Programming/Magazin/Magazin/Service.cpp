#include "Service.h"
#include <assert.h>
#include <functional>
#include <algorithm>
#include <vector>

using std::sort;

void Magazin::adaugaProdus(string nume, string tip, string producator, double pret) {
	Produs p{ nume, tip, producator, pret };
	val.valid(p);
	repo.store(p);
	undo.push_back(std::make_unique<undoAdd>(repo, p));
}

void Magazin::stergeProdus(string nume, string tip, string producator, double pret) {
	Produs p{ nume, tip, producator, pret };
	val.valid(p);
	undo.push_back(std::make_unique<undoDel>(repo, p));
	repo.remove(p);
}

const Produs& Magazin::cautaProdus(string nume) {
	return repo.find(nume);
}

void Magazin::modificaProdus(string nume, string tip_nou, string producator_nou, double pret_nou) {
	Produs p_nou(nume, tip_nou, producator_nou, pret_nou);
	val.valid(p_nou);
	const Produs produs = repo.find(nume);
	undo.push_back(std::make_unique<undoUpdate>(repo, produs));
	repo.modific(p_nou);
}

/*vector<Produs> Magazin::filter(function<bool(const Produs&)> fct) {
	vector<Produs> filtered;
	//for (const auto& song : repo.getProduse()) {
	for (int i = 0; i < repo.getProduse().size(); i++){
		if (fct(repo.getProduse().at(i))) {
			string nume, tip, producator;
			double pret;
			nume = repo.getProduse().at(i).getNume();
			tip = repo.getProduse().at(i).getTip();
			producator = repo.getProduse().at(i).getProducator();
			pret = repo.getProduse().at(i).getPret();
			Produs p = { nume,tip,producator,pret };
			filtered.push_back(p);
		}
	}
	return filtered;
}*/

vector<Produs> Magazin::filtrareTip(string tip) {
	/*return filter([tip](const Produs& m) {
		return m.getTip() == tip;
		});*/

	const vector<Produs>& all = getproduse();
	vector<Produs> filtered;
	std::copy_if(all.begin(), all.end(), back_inserter(filtered),
		[tip](const Produs& p) {
			return p.getTip() == tip;
		});

	return filtered;
}

vector<Produs> Magazin::filtrarePret(double pretStart, double pretEnd) {
	/*return filter([=](const Produs& m) {
		return m.getPret() >= pretStart && m.getPret() <= pretEnd;
		});*/


	const vector<Produs>& all = getproduse();
	vector<Produs> filtered;
	std::copy_if(all.begin(), all.end(), back_inserter(filtered),
		[=](const Produs& p) {
			return p.getPret() > pretStart && p.getPret() < pretEnd;
		});

	return filtered;
}


/*vector<Produs> Magazin::generalSort(bool(*maiMicF)(const Produs&, const Produs&)) {
	vector<Produs> v{ repo.getProduse() };
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = i + 1; j < v.size(); j++) {
			if (!maiMicF(v.at(i), v.at(j))) {
				//interschimbam
				Produs aux = v.at(i);
				v.set(v.at(j), i);
				v.set(aux, j);
			}
		}
	}
	return v;
}*/



vector<Produs> Magazin::sortByPret() {
	vector<Produs> sortedCopy{ repo.getProduse() };
	sort(sortedCopy.begin(), sortedCopy.end(), cmpPret);
	return sortedCopy;
}

vector<Produs> Magazin::sortByProdNume() {
	vector<Produs> sortedCopy{ repo.getProduse() };
	sort(sortedCopy.begin(), sortedCopy.end(), cmpProdNume);
	return sortedCopy;
}


const vector<Produs>& Magazin::getproduse() noexcept {
	return this->repo.getProduse();
}


int Magazin::UNDO()
{
	if (undo.empty())
		return -1;
	undo.back()->doUndo();
	undo.pop_back();
	return 0;
}












void Magazin::addCos(string nume, string tip) {
	const auto& produs = repo.find(nume);
	cosul_curent.add(produs);
}

int Magazin::addRandomCos(int nr) {
	cosul_curent.addRandom(this->getproduse(), nr);
	return cosul_curent.getAll().size();
}

void Magazin::empty() {
	cosul_curent.empty();
}

const vector<Produs>& Magazin::getCos() {
	return cosul_curent.getAll();
}

/*
unordered_map<string, int> Magazin::map() {
	unordered_map<string, int> prodFreq;

	for (const auto& i : repo.getProduse()) {
		prodFreq[i.getTip()]++;
	}

	return prodFreq;
};*/

bool Magazin::exportCos(const string fname, const string type)
{
	return cosul_curent.Export(fname, type);
}



void testUndo() {
	ProduseRepo testr;
	ProdusVal vl;
	Magazin tests{ testr, vl };

	tests.adaugaProdus("nume1", "tip1", "prod1", 1.99);
	tests.modificaProdus("nume1", "tip2", "prod2", 100);
	tests.stergeProdus("nume1", "tip2", "prod2", 100);
	assert(tests.getproduse().size() == 0);
	tests.UNDO();
	assert(tests.getproduse().size() == 1);
	tests.UNDO();
	assert(tests.getproduse().at(0).getTip() == "tip1");
	tests.UNDO();
	assert(tests.getproduse().size() == 0);
}


void testadaugaProdus() {
	ProduseRepo testr;
	ProdusVal vl;
	Magazin tests{ testr, vl };

	tests.adaugaProdus("nume1", "tip1", "prod1", 1.99);
	tests.adaugaProdus("nume2", "tip2", "prod2", 5.99);
	tests.adaugaProdus("nume3", "tip3", "prod3", 9.99);

	assert(tests.getproduse().size() == 3);

	try {
		tests.adaugaProdus("Pictures of Home", "Deep Purple", "rock", 1.22);
		assert(true);
	}
	catch (Validation&) {
		assert(false);
	}

	try {
		tests.adaugaProdus("", "Deep Purple", "rock", 2.24);
		assert(false);
	}
	catch (Validation& ve) {
		assert(ve.getErrors() == "Numele trebuie sa aiba cel putin 2 litere!\n");
	}


	try {
		tests.adaugaProdus("Smoke on the Water", "", "rock", 2.24);
		assert(false);
	}
	catch (Validation&) {
		assert(true);
	}


	try {
		tests.adaugaProdus("High Hopes", "Pink Floyd", "rock", 12000);
		assert(false);
	}
	catch (Validation&) {
		assert(true);
	}

	try {
		tests.adaugaProdus("Child in Time", "Deep Purple", "", 16);
		assert(false);
	}
	catch (Validation&) {
		assert(true);
	}
}

void teststergeProdus() {
	ProduseRepo testr;
	ProdusVal vl;
	Magazin tests{ testr, vl };

	tests.adaugaProdus("nume1", "tip1", "prod1", 1.99);
	tests.adaugaProdus("nume2", "tip2", "prod2", 5.99);
	tests.adaugaProdus("nume3", "tip3", "prod3", 9.99);

	assert(tests.getproduse().size() == 3);

	tests.stergeProdus("nume1", "tip1", "prod1", 1.99);

	assert(tests.getproduse().size() == 2);

	assert(tests.getproduse().at(0).getPret() == 5.99);
}

void testcautaProdus() {
	ProduseRepo testr;
	ProdusVal vl;
	Magazin tests{ testr, vl };

	tests.adaugaProdus("nume1", "tip1", "prod1", 1.99);
	tests.adaugaProdus("nume2", "tip2", "prod2", 5.99);
	tests.adaugaProdus("nume3", "tip3", "prod3", 9.99);

	assert(tests.cautaProdus("nume1").getPret() == 1.99);
	assert(tests.cautaProdus("nume2").getPret() == 5.99);
	assert(tests.cautaProdus("nume3").getPret() == 9.99);
}

void testmodificareProdus() {
	ProduseRepo testr;
	ProdusVal vl;
	Magazin tests{ testr, vl };

	tests.adaugaProdus("nume1", "tip1", "prod1", 1.99);
	tests.adaugaProdus("nume2", "tip2", "prod2", 5.99);

	tests.modificaProdus("nume1", "tip2", "prod2", 5.99);

	assert(tests.getproduse().at(1).getPret() == tests.getproduse().at(0).getPret());
	assert(tests.getproduse().at(1).getProducator() == tests.getproduse().at(0).getProducator());
}

void testFilterService() {
	ProduseRepo testRepo;
	ProdusVal vl;
	Magazin testService{ testRepo, vl };

	testService.adaugaProdus("Pasarea Calandrinon", "Phoenix", "folk-rock", 3.42);
	testService.adaugaProdus("Baba Novak", "Phoenix", "folk-rock", 8.31);
	testService.adaugaProdus("Apocalipsa", "Phoenix", "folk-rock", 5.27);
	testService.adaugaProdus("Fantanile", "Alternosfera", "alternative rock", 4.52);
	testService.adaugaProdus("Ploile Nu Vin", "Alternosfera", "alternative rock", 3.45);
	testService.adaugaProdus("Padure Verde", "Via Daca", "maybe folk", 3.2);

	vector<Produs> melodiiFolkRock = testService.filtrareTip("Phoenix");
	assert(melodiiFolkRock.size() == 3);
	vector<Produs> melodiiHeavyMetal = testService.filtrareTip("heavy metal");
	assert(melodiiHeavyMetal.size() == 0);


	vector<Produs> melodii1 = testService.filtrarePret(2.15, 3.44);
	assert(melodii1.size() == 2);
	vector<Produs> melodii2 = testService.filtrarePret(9, 10);
	assert(melodii2.size() == 0);

}

void testSortService() {

	ProduseRepo testRepo;
	ProdusVal vl;
	Magazin testService{ testRepo, vl };

	testService.adaugaProdus("Pasarea Calandrinon", "Phoenix", "folk-rock", 3.42);
	testService.adaugaProdus("Baba Novak", "Phoenix", "folk-rock", 8.31);
	testService.adaugaProdus("Apocalipsa", "Phoenix", "folk-rock", 5.27);
	testService.adaugaProdus("Fantanile", "Alternosfera", "alternative rock", 4.52);
	testService.adaugaProdus("Ploile Nu Vin", "Alternosfera", "alternative rock", 3.45);
	testService.adaugaProdus("Padure Verde", "Via Daca", "maybe folk", 3.2);

	vector<Produs> sortedByDurata = testService.sortByPret();
	assert(sortedByDurata.at(0).getNume() == "Padure Verde");
	assert(sortedByDurata.at(1).getNume() == "Pasarea Calandrinon");
	assert(sortedByDurata.at(2).getNume() == "Ploile Nu Vin");
	assert(sortedByDurata.at(5).getNume() == "Baba Novak");

	vector<Produs> sortedByArtistSong = testService.sortByProdNume();
	assert(sortedByArtistSong.at(0).getTip() == "Alternosfera");
	assert(sortedByArtistSong.at(0).getNume() == "Fantanile");

	assert(sortedByArtistSong.at(2).getTip() == "Phoenix");
	assert(sortedByArtistSong.at(2).getNume() == "Apocalipsa");

	assert(sortedByArtistSong.at(5).getTip() == "Via Daca");
	assert(sortedByArtistSong.at(5).getNume() == "Padure Verde");

}

void testad() {
	ProduseRepo testr;
	ProdusVal vl;
	Magazin tests{ testr, vl };

	tests.adaugaProdus("nume1", "tip1", "prod1", 1.99);
	tests.adaugaProdus("nume2", "tip2", "prod2", 5.99);
	tests.adaugaProdus("nume3", "tip3", "prod3", 9.99);

	tests.addCos("nume1", "tip1");
	assert(tests.getCos().size() == 1);
	tests.empty();
	assert(tests.getCos().size() == 0);

	tests.addRandomCos(2);
	assert(tests.getCos().size() == 2);
}

void testeService() {
	testad();
	testadaugaProdus();
	teststergeProdus();
	testcautaProdus();
	testmodificareProdus();
	testSortService();
	testFilterService();
	testUndo();
}
