#pragma once
#include "Repository.h"
#include "validators.h"
#include "Cos.h"
#include <unordered_map>
#include <functional>
#include "Undo.h"
using namespace std;
using std::function;

class Raport {
	friend class Produs;

public:
	unordered_map<string, int> map(vector<Produs> vc) {
		unordered_map<string, int> prodFreq;

		for (const auto& i : vc) {
			prodFreq[i.getTip()]++;
		}

		return prodFreq;
	};
};

class Magazin {
private:
	ProduseRepo& repo;
	ProdusVal& val;

	vector<std::unique_ptr<Undo>> undo;

	//vector<Produs> filter(function<bool(const Produs&)> fct);
	
	//vector<Produs> generalSort(bool(*maiMicF)(const Produs&, const Produs&));

	Cos cosul_curent;

public:
	Magazin(ProduseRepo& produseR, ProdusVal& val) noexcept :repo{ produseR }, val{ val } {};
    
	Magazin(const Magazin& o) = delete;

	void adaugaProdus(string nume, string tip, string producator, double pret);

	void stergeProdus(string nume, string tip, string producator, double pret);

	const Produs& cautaProdus(string nume);

	void modificaProdus(string nume, string tip_nou, string producator_nou, double pret_nou);

	const vector<Produs>& getproduse() noexcept ;

	vector<Produs> filtrareTip(string tip);

	vector<Produs> filtrarePret(double pretStart, double pretEnd);

	vector<Produs> sortByPret();

	vector<Produs> sortByProdNume();

	void addCos(string nume, string tip);

	int addRandomCos(int nr);

	void empty();

	const vector<Produs>& getCos();

	//unordered_map<string, int> map();

	bool exportCos(const string fname, const string type);

	int UNDO();
};

void testeService();