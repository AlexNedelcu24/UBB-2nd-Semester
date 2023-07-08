#pragma once
#include "UI.h"
#include <iostream>
using namespace std;
void Console::printMeniu() {
	cout << "Comezile sunt:" << endl;
	cout << "1. Adauga produs" << endl;
	cout << "2. Sterge produs" << endl;
	cout << "3. Modificare produs" << endl;
	cout << "4. Cauta podus" << endl;
	cout << "5. Afisare produse" << endl;
    cout << "6. Filtreaza" << endl;
	cout << "7. Sorteaza" << endl;
	cout << "8. Cos" << endl;
	cout << "9. Raport" << endl;
	cout << "10. Undo" << endl;
	cout << "11. Exit" << endl;
}

void Console::printCos() {
	cout << "MENIU COS" << endl;
	cout << "1. Adauga produs in cos" << endl;
	cout << "2. Adauga produse random in cos" << endl;
	cout << "3. Goleste cosul" << endl;
	cout << "4. Afiseaza cosul curent" << endl;
	cout << "5. Export cos" << endl;
	cout << "6. Inapoi la meniul principal" << endl;
}

void Console::uiAdauga() {
	string nume, tip, producator;
	double pret;
	cout << "Introdu numele produsului:";
	getline(cin >> ws, nume);

	cout << "Introdu tipul produsului:";
	getline(cin >> ws, tip);

	cout << "Introdu producatorul produsului:";
	getline(cin >> ws, producator);

	cout << "Introdu pretul produsului:";
	cin >> pret;

	try {
		srv.adaugaProdus(nume, tip, producator, pret);
	}
	catch (RepoException& re) {
		cout << re.getErrors();
	}
	catch (Validation& ve) {
		cout << "Produsul nu este valid!" << endl;
		cout << ve.getErrors();
	}

}

void Console::uiSterge() {
	string nume, tip, producator;
	double pret;
	cout << "Introdu numele produsului:";
	getline(cin >> ws, nume);

	cout << "Introdu tipul produsului:";
	getline(cin >> ws, tip);

	cout << "Introdu producatorul produsului:";
	getline(cin >> ws, producator);

	cout << "Introdu pretul produsului:";
	cin >> pret;

	try {
		srv.stergeProdus(nume, tip, producator, pret);
	}
	catch (RepoException& re) {
		cout << re.getErrors();
	}
	catch (Validation& ve) {
		cout << "Produsul nu este valid!" << endl;
		cout << ve.getErrors();
	}
}

void Console::uiCauta() {
	string nume;

	cout << "Introdu numele produsului:";
	getline(cin >> ws, nume);

	//cout << "Introdu tipul produsului:";
	//getline(cin >> ws, tip);

	Produs p = srv.cautaProdus(nume);
	cout << "Produsul cautat este: " << endl;
	cout << "Nume: " << p.getNume() << "  Tip: " << p.getTip() << "  Producator: " << p.getProducator() << "  Pret: " << p.getPret() << endl;
}

void Console::uiModifica() {
	string nume;
	cout << "Introdu numele produsului:";
	getline(cin >> ws, nume);

	string tip_nou, producator_nou;
	double pret_nou;

	cout << "Introdu tipul noului produs:";
	getline(cin >> ws, tip_nou);

	cout << "Introdu producatorul noului produs:";
	getline(cin >> ws, producator_nou);

	cout << "Introdu pretul noului produs:";
	cin >> pret_nou;

	try {
		srv.modificaProdus(nume, tip_nou, producator_nou, pret_nou);
	}
	catch (RepoException& re) {
		cout << re.getErrors();
	}
	catch (Validation& ve) {
		cout << "Produsul nu este valid!" << endl;
		cout << ve.getErrors();
	}
}

void Console::uiFiltreaza() {
	cout << "Criteriul de filtrare este (tip/pret):";
	string criteriu;
	cin >> criteriu;

	if (criteriu == "tip") {
		cout << "Tipul cautat este:" << endl;
		string searchedTip;
		cin >> searchedTip;

		vector<Produs> produse = srv.filtrareTip(searchedTip);
		if (produse.size() == 0)
			cout << "Nu exista produse in lista!" << endl;
		else
			for (int i = 0; i < produse.size(); i++) {
				Produs produs = produse.at(i);
				//for (const auto& produs : produse) {
				cout << "Nume: " << produs.getNume() << "  Tip: " << produs.getTip() << "  Producator: " << produs.getProducator() << "  Pret: " << produs.getPret() << endl;
			}

	}
	else if (criteriu == "pret") {
		double pretStart, pretEnd;
		cout << "Limita inferioara a pretului este:" << endl;
		cin >> pretStart;
		cout << "Limita superioara a pretului este:" << endl;
		cin >> pretEnd;


		vector<Produs> produse = srv.filtrarePret(pretStart, pretEnd);
		if (produse.size() == 0)
			cout << "Nu exista produse in lista!" << endl;
		else
			for (int i = 0; i < produse.size(); i++) {
				Produs produs = produse.at(i);
				//for (const auto& produs : produse) {
				cout << "Nume: " << produs.getNume() << "  Tip: " << produs.getTip() << "  Producator: " << produs.getProducator() << "  Pret: " << produs.getPret() << endl;
			}
	}

	else
		cout << "Nu se poate sorta dupa criteriul dat." << endl;

}

void Console::uiSort() {
	cout << "Criteriul de sortare este (pret/producator+nume):";
	string criteriu;
	cin >> criteriu;

	if (criteriu == "pret") {
		vector<Produs> produse = srv.sortByPret();
		if (produse.size() == 0)
			cout << "Nu exista produse in lista!" << endl;
		else
			for (int i = 0; i < produse.size(); i++) {
				Produs produs = produse.at(i);
				//for (const auto& produs : produse) {
				cout << "Nume: " << produs.getNume() << "  Tip: " << produs.getTip() << "  Producator: " << produs.getProducator() << "  Pret: " << produs.getPret() << endl;
			}
	}
	else if (criteriu == "producator+nume") {
		vector<Produs> produse = srv.sortByProdNume();
		if (produse.size() == 0)
			cout << "Nu exista produse in lista!" << endl;
		else
			for (int i = 0; i < produse.size(); i++) {
				Produs produs = produse.at(i);
				//for (const auto& produs : produse) {
				cout << "Nume: " << produs.getNume() << "  Tip: " << produs.getTip() << "  Producator: " << produs.getProducator() << "  Pret: " << produs.getPret() << endl;
			}
	}
	else
		cout << "Nu se poate sorta dupa criteriul dat." << endl;
}


void Console::uiAddCos() {
	string nume, tip;
	cout << "Numele produsului este:";
	getline(cin >> ws, nume);

	cout << "Tipul produsului este:";
	getline(cin >> ws, tip);

	try {
		srv.addCos(nume, tip);
		cout << "Produsul s-a adaugat cu succes in cos." << endl;
	}
	catch (RepoException& re) {
		cout << re.getErrors();
	}
	catch (Validation& ve) {
		cout << "Produsul nu este valid!" << endl;
		cout << ve.getErrors();
	}
}

void Console::uiAddRandomCos() {
	int nr;
	cout << "Cate produse sa se adauge in cos?";
	cin >> nr;


	try {
		int nr_add = srv.addRandomCos(nr);
		cout << "S-au adaugat " << nr_add << " produse in cos." << endl;
	}
	catch (RepoException& re) {
		cout << re.getErrors();
	}
}

void Console::uiEmptyCos() {
	srv.empty();
	cout << "S-au sters toate produsele din cosul curent." << endl;
}



void Console::printProduse(const vector<Produs>& produse) {

	if (produse.size() == 0)
		cout << "Nu exista produse in lista!" << endl;
	else 
		for (int i=0; i<produse.size(); i++) {
			Produs produs = produse.at(i);
		//for (const auto& produs : produse) {
			cout << "Nume: " << produs.getNume() << "  Tip: " << produs.getTip() << "  Producator: " << produs.getProducator() << "  Pret: " << produs.getPret() << endl;
		}
}


/*
void Console::raport() {
	unordered_map<string, int>::iterator p;
	//for (p = srv.map().begin(); p != srv.map().end(); p++)
	for(const auto& p : srv.map())
		cout << "(" << p.first << ", " << p.second << ")\n";
		cout << '\n';
}
*/

void Console::raport() {
	unordered_map<string, int>::iterator p;
	Raport m;
	for (const auto& p : m.map(srv.getproduse()))
		cout << "(" << p.first << ", " << p.second << ")\n";
	cout << '\n';
}


void Console::uiExportCos()
{
	string fname, type;
	cout << "Numele fisierului este: ";
	cin >> fname;
	cout << "Extensia fisierului este(html/csv): ";
	cin >> type;
	if (srv.exportCos(fname, type))
		cout << "\nExportul s-a realizat cu succes!\n";
	else
		cout << "\nExportul nu a fost realizat\n";
}

void Console::uiCos() {
	int cmd;
	int start = 1;
	while (start) {
		printCos();
		cout << "Comanda este:";
		cin >> cmd;
		switch (cmd)
		{
		case 1:
			uiAddCos();
			break;
		case 2:
			uiAddRandomCos();
			break;
		case 3:
			uiEmptyCos();
			break;

		case 4:
			printProduse(srv.getCos());
			break;

		case 5:
			uiExportCos();
			break;
		case 6:
			start = 0;
			break;
		default:
			break;
		}

	}
}


void Console::run() {
	constexpr int start = 1;
	int cmd = 6;
	while (start) {
		cout << endl;
		printMeniu();
		cout << "Introdu comanda:";
		cin >> cmd;
		if (cmd == 1) {
			uiAdauga();
		}
		else if (cmd == 2) {
			uiSterge();
		}
		else if (cmd == 3) {
			uiModifica();
		}
		else if (cmd == 4) {
			uiCauta();
		}
		else if(cmd == 5) {
			printProduse(srv.getproduse());
		}
		else if (cmd == 6) {
			uiFiltreaza();
		}
		else if (cmd == 7) {
			uiSort();
		}
		else if (cmd == 8) {
			uiCos();
		}
		else if (cmd == 9) {
			raport();
		}
		else if (cmd == 10) {
			if (srv.UNDO() == -1)
				cout << "Nu se mai poate face undo!\n";
			else printProduse(srv.getproduse());
		}
		else if (cmd == 11) {
			break;
		}
	}
}